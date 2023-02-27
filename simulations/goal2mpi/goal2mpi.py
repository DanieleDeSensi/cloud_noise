#!/usr/bin/env python3
import sys
import argparse
import collections
from io import StringIO 

def print_statement(id, outfile, line, mpi_req_handles, args):
    # l1: send 1024b to 2 tag 0
    if "send" in line:
        size = line.split(" ")[2].split("b")[0].strip()
        dest = line.split(" ")[4].strip()
        tag = line.split(" ")[6].strip()
        if int(size) > int(args.message_size):
            sys.exit("Size invalid")
        if args.nb_send:
            mpi_req_handle = "(mpi_reqs[" + id.split("l")[1] + "])"
            mpi_req_handles[id] = mpi_req_handle
            outfile.write("        MPI_Isend(buffer, " + str(size) + ", MPI_BYTE, " + str(dest) + ", " + str(tag) + ", MPI_COMM_WORLD, &" + mpi_req_handle + ");\n")
        else:
            outfile.write("        MPI_Send(buffer, " + str(size) + ", MPI_BYTE, " + str(dest) + ", " + str(tag) + ", MPI_COMM_WORLD);\n")
    elif "recv" in line:
        size = line.split(" ")[2].split("b")[0].strip()
        src = line.split(" ")[4].strip()
        tag = line.split(" ")[6].strip()
        if int(size) > int(args.message_size):
            sys.exit("Size invalid")
        mpi_req_handle = "(mpi_reqs[" + id.split("l")[1] + "])"
        mpi_req_handles[id] = mpi_req_handle
        outfile.write("        MPI_Irecv(buffer, " + str(size) + ", MPI_BYTE, " + str(src) + ", " + str(tag) + ", MPI_COMM_WORLD, &" + mpi_req_handle + ");\n")
        #outfile.write("        MPI_Recv(buffer, " + str(size) + ", MPI_BYTE, " + str(src) + ", " + str(tag) + ", MPI_COMM_WORLD, MPI_STATUS_IGNORE);\n")
    elif "calc" in line and not args.skip_compute:
        time_ns = line.split(" ")[2].strip()
        if int(time_ns) != 0:
            outfile.write("        my_nanosleep(" + time_ns + ");\n")

def print_statement_with_deps(outfile, id, statements, dependencies, printed, mpi_req_handles, args):  
    if id in printed:
        return
    elif id in dependencies:
        # Check if it has dependencies        
        deps = dependencies[id]
        for d in deps:
            if d not in printed: # Check if dependecies have been already printed
                print_statement_with_deps(outfile, d, statements, dependencies, printed, mpi_req_handles, args)
            if d in list(mpi_req_handles.keys()):
                assert(d in printed)
                mpi_req_handle = mpi_req_handles[d]
                outfile.write("        MPI_Wait(&" + mpi_req_handle + ", MPI_STATUS_IGNORE);\n")
                del mpi_req_handles[d]
        print_statement(id, outfile, statements[id], mpi_req_handles, args)
        printed[id] = ""
    elif id not in printed:
        print_statement(id, outfile, statements[id], mpi_req_handles, args)
        printed[id] = ""

def main():
    parser = argparse.ArgumentParser(description='Translates GOAL files to MPI code.')
    parser.add_argument('--input', help='Input file.')
    parser.add_argument('--output', help='Output file.')
    parser.add_argument('--warmup_iterations', help='Warmup iterations.', default=10)
    parser.add_argument('--iterations', help='Iterations.', default=1000)
    parser.add_argument('--prioritize_receive', help='Prioritizes recvs.', action="store_true")
    parser.add_argument('--message_size', help='Message size.')
    parser.add_argument('--skip_compute', help='Skips compute.', action="store_true")
    parser.add_argument('--use_tests', help='Replaces waits with tests.', action="store_true")
    parser.add_argument('--nb_send', help='Uses nonblocking send.', action="store_true")
    args = parser.parse_args()

    outfile = open(args.output, 'w')
    infile = open(args.input, 'r')
    outfile.write("#include <stdio.h>\n")
    outfile.write("#include <stdlib.h>\n")
    outfile.write("#include <mpi.h>\n")
    outfile.write("#include <time.h>\n")
    outfile.write("#include <string.h>\n")
    outfile.write("#include <unistd.h>\n")
    outfile.write("#define add_time(now, expected, s, ns){expected.tv_sec = now.tv_sec + add_s; expected.tv_nsec = now.tv_nsec + add_ns;}\n")
    outfile.write("#define cmp_time_leq(time1, time2) (time1.tv_sec < time2.tv_sec ? 1 : (time1.tv_sec == time2.tv_sec && time1.tv_nsec < time2.tv_nsec ? 1 : 0))\n")
    outfile.write("void my_nanosleep(int sleep_time_ns){\n")
    outfile.write("    long add_s, add_ns, measured_time;\n")
    outfile.write("    struct timespec now, expected;\n")
    outfile.write("    // busy waiting\n")
    outfile.write("    if (sleep_time_ns >= 1e9){\n")
    outfile.write("        add_s = sleep_time_ns / 1e9;\n")
    outfile.write("        add_ns = (long)sleep_time_ns % (long)1e9;\n")
    outfile.write("    }else{\n")
    outfile.write("        add_s = 0;\n")
    outfile.write("        add_ns = sleep_time_ns;\n")
    outfile.write("    }\n")
    outfile.write("\n")
    outfile.write("    clock_gettime(CLOCK_REALTIME, &now);\n")
    outfile.write("    add_time(now, expected, add_s, add_ns);\n")
    outfile.write("    while (cmp_time_leq(now, expected)){\n")
    outfile.write("        clock_gettime(CLOCK_REALTIME, &now);\n")
    outfile.write("    }\n")
    outfile.write("}\n")
    outfile.write("int main(int argc, char** argv){\n")
    outfile.write("    char* buffer = (char*) malloc(sizeof(char)*" + str(args.message_size) + ");\n")
    outfile.write("    double* samples = (double*) malloc(sizeof(double)*" + str(args.iterations) + ");\n")
    outfile.write("    double* samples_all;\n")
    outfile.write("    long i, r;\n")
    outfile.write("    MPI_Init(&argc, &argv);\n")
    outfile.write("    int rank, comm_size;\n")
    outfile.write("    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);\n")
    outfile.write("    MPI_Comm_rank(MPI_COMM_WORLD, &rank);\n")
    outfile.write("    if(rank == 0){\n")
    outfile.write("        samples_all = (double*) malloc(sizeof(double)*comm_size*" + str(args.iterations) + ");\n")
    outfile.write("    }\n")
    outfile.write("    for(i = -" + str(args.warmup_iterations) + "; i < " + str(args.iterations) + "; i++){\n")
    outfile.write("        usleep(1);\n")
    outfile.write("        switch(rank){\n")
    statements = {}
    dependencies = {}
    printed = {}
    mpi_req_handles = {}
    for line in infile.readlines():
        if "num_ranks" in line:
            continue
        elif "{" in line: # Open            
            rank = line.split(" ")[1]
            outfile.write("        case " + rank + ":{\n")
        elif "}" in line: # Close
            outfile.write("        MPI_Request mpi_reqs[" + str(len(statements) + 1) + "];\n")
            outfile.write("        int flags[" + str(len(statements) + 1) + "];\n")
            outfile.write("        int completed[" + str(len(statements) + 1) + "];\n")
            outfile.write("        memset(flags, 0, sizeof(flags));\n")
            outfile.write("        memset(completed, 0, sizeof(completed));\n")
            outfile.write("        int completed_tot = 0;\n")
            outfile.write("        MPI_Barrier(MPI_COMM_WORLD);\n")
            outfile.write("        double start_time = MPI_Wtime();\n")
            statements_sorted = collections.OrderedDict(statements)
            # Print first the statements without dependencies (first recvs)
            if args.prioritize_receive:
                for id in statements_sorted:
                    if id not in dependencies and id not in printed and "recv" in statements[id]:
                        print_statement(id, outfile, statements[id], mpi_req_handles, args)
                        printed[id] = ""
            # Print first the statements without dependencies (then the others)
            for id in statements_sorted:
                if id not in dependencies and id not in printed:
                    print_statement(id, outfile, statements[id], mpi_req_handles, args)
                    printed[id] = ""
            # Now print the remaining statements            
            outfile.write("        do{\n")
            completed_tot = 0
            for id in statements_sorted:
                stringio = StringIO()
                print_statement_with_deps(stringio, id, statements, dependencies, printed, mpi_req_handles, args)
                lid = 0
                ind = ""
                flag_id = None
                for line in stringio.getvalue().split("\n"):
                    if line.strip() == "": # Skip empty lines
                        continue
                    # Replace the first wait of the block with a test
                    if lid == 0 and "Wait" in line and args.use_tests:
                        ind = "            "
                        line = line.replace("Wait", "Test")
                        flag_id = line.split("[")[1].split("]")[0]
                        line = "        " + line.replace(", MPI_STATUS_IGNORE", ", &(flags[" + flag_id  + "]), MPI_STATUS_IGNORE")                        
                        outfile.write("            if(completed[" + flag_id + "] == 0){\n")
                        outfile.write(line + "\n")
                        outfile.write("                if(flags[" + flag_id + "] == 1){\n")
                    else:
                        outfile.write(ind + line + "\n")                    
                    #outfile.write(line)
                    lid += 1
                if flag_id is not None:
                    outfile.write("                    completed[" + flag_id + "] = 1;\n")
                    outfile.write("                    completed_tot += 1;\n")
                    outfile.write("                }\n")
                    outfile.write("            }\n")
                    completed_tot += 1

            outfile.write("        }while(completed_tot < " + str(completed_tot) + ");\n")
            # Now wait for the remaining irecv
            for k in mpi_req_handles:
                mpi_req_handle = mpi_req_handles[k]
                outfile.write("        MPI_Wait(&" + mpi_req_handle + ", MPI_STATUS_IGNORE);\n")

            outfile.write("        if(i >= 0){\n")
            outfile.write("            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);\n")
            outfile.write("        }\n")
            outfile.write("        break;\n")
            outfile.write("        }\n")
            statements.clear()
            dependencies.clear()
            printed.clear()
            mpi_req_handles.clear()
        else: # Body
            if "send" in line or "recv" in line or "calc" in line:
                id = line.split(":")[0]
                statements[id] = line
            elif "requires" in line:
                # l2 requires l1
                id = line.split(" ")[0]
                depends_on = line.split(" ")[2].strip()
                if id not in dependencies:
                    dependencies[id] = [depends_on]
                else:
                    dependencies[id] += [depends_on]
            else:
                if line.strip() != "":
                    sys.exit("Unknown line " + line)
    outfile.write("        }\n")
    outfile.write("    }\n")
    
    outfile.write("    MPI_Gather(samples, " + str(args.iterations) + ", MPI_DOUBLE, samples_all, " + str(args.iterations) + ", MPI_DOUBLE, 0, MPI_COMM_WORLD);\n")
    outfile.write("    if(rank == 0){\n")
    outfile.write("        printf(\"#MessageSize \");\n")
    outfile.write("        for(r = 0; r < comm_size; r++){\n")
    outfile.write("            printf(\"Rank%ldTime(us) \", r);\n")
    outfile.write("        }\n")
    outfile.write("        printf(\"\\n\");\n")
    outfile.write("        for(i = 0; i < " + str(args.iterations) + "; i++){\n")
    outfile.write("            printf(\"%d \", " + str(args.message_size) + ");\n")
    outfile.write("            for(r = 0; r < comm_size; r++){\n")
    outfile.write("               printf(\"%f \", samples_all[r*" + str(args.iterations) + " + i]);\n")
    outfile.write("            }\n")
    outfile.write("            printf(\"\\n\");\n")
    outfile.write("        }\n")    
    outfile.write("    }\n")

    #outfile.write("    MPI_Reduce(samples, samples_max, " + str(args.iterations) + ", MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);\n")
    #outfile.write("    if(rank == 0){\n")
    #outfile.write("        for(size_t i = 0; i < " + str(args.iterations) + "; i++){\n")
    #outfile.write("            printf(\"%d %f\", " + str(args.message_size) + ", samples_max[i]);\n")
    #outfile.write("        }\n")
    #outfile.write("    }\n")
    
    
    outfile.write("    MPI_Finalize();\n")
    outfile.write("    return 0;\n")
    outfile.write("}\n")

if __name__ == "__main__":
    main()