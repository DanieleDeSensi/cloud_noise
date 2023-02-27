FROM ubuntu:22.04
LABEL Description="Cloud noise simulations and plotting"
SHELL ["/bin/bash", "-c"]

# Install dependencies
RUN apt-get update && apt-get -y --no-install-recommends install \
    gcc \
    build-essential \
    gengetopt \
    libgraphviz-dev \
    re2c \
    curl \
    xz-utils \
    parallel \
    python3 \
    python3-pip

# Create user
RUN useradd -ms /bin/bash user
USER user
WORKDIR /home/user
ENV PATH="/home/user/.local/bin:${PATH}"

# Install python packages
RUN pip3 install --user pandas seaborn matplotlib