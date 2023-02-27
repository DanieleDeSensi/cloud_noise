#!/usr/bin/env python3
import sys

from numpy import place
def get_loggp_params(provider, instance, suffix, placement="Same Rack"):
    if provider == "AWS":                
        if instance == "HPC (Metal)":
            if suffix == "y16":
                return (28, 0, 0, 0.00020, 65536)
            elif suffix == "x1":
                if placement == "Same Rack":
                    #return (21.5, 3.5, 0, 0.00017, 65536)
                    return (28, 0, 0, 0.00017, 65536)
                else:
                    #return (21.5, 3.5, 22, 0.0003, 65536)
                    return (28, 0, 22, 0.0003, 65536)
            else:
                sys.exit("Unkown suffix")
        elif instance == "Normal":
            if suffix == "y16":
                return (21.7, 20, 22, 0.000289, 524288)
            elif suffix == "x1":
                return (21.7, 2, 22, 0.0004, 32768)
            else:
                sys.exit("Unkown suffix")
        else:
            sys.exit("Unknown instance")
    elif provider == "GCP":
        if instance == "HPC":
            if suffix == "y16":
                return (20, 17, 3, 0.00012, 1048576)
            elif suffix == "x1":
                return (23, 0, 0, 0.00039, 65536)
            else:
                sys.exit("Unkown suffix")
        elif instance == "Normal":
            if suffix == "y16":
                return (20, 24, 3.99, 0.00020, 1048576)
            elif suffix == "x1":
                return (20, 2, 3.99, 0.00042, 65536)
            else:
                sys.exit("Unkown suffix")
        else:
            sys.exit("Unknown instance")
    elif provider == "Azure":
        if instance == "HPC":
            #return (1.64, 0.5, 0, 0.000087, 4096)
            return (1.3, 0.15, 1.5, 0.000086, 4096)
        elif instance == "HPC (200 Gb/s)":
            return (1.7, 0, 1, 0.000046, 4096)
        elif instance == "Normal":
            if suffix == "y2":
                return (30, 5, 0.18, 0.0006, 262144)
            elif suffix == "x1":
                return (30, 5, 0.18, 0.0011, int(262144/2))
            else:
                sys.exit("Unkown suffix")
        else:
            sys.exit("Unknown instance")
    elif provider == "Daint":
        if instance == "HPC (Metal)":
            if placement == "Same Rack":
                return (.5, .0, 6, 0.00011, 4096)
                #return (1, 0.0, 2, 0.00015, 4096)
            else:
                return (.5, .0, 6, 0.00014, 4096)
                #return (1, 0.0, 2, 0.00015, 4096) # Same group, different cabinets              
    elif provider == "Alps":
        if instance == "HPC (Metal)":
            if placement == "Same Rack":
                return (1.9, 0.23, 0, 0.000079, 4096) # Good              
                #return (5, 0.0, 0, 0.00008, 4096) # Good
            else:
                return (1.9, 0.23, 0, 0.000092, 4096) # Good              
                #return (5, 0.0, 0, 0.00008, 4096) # Good              
    elif provider == "DEEP-EST":
        if instance == "HPC (Metal)":
            return (1.6, 0.35, 5.5, 0.000089, 4096)
    elif provider == "Oracle":
        if instance == "HPC (Metal)":
            if placement == "Same Rack":
                return (1.6, 0.15, 5, 0.0001, 4096)
            else:
                return (1.6, 0.15, 5, 0.000105, 4096)
    else:
        sys.exit("Unknown provider")
