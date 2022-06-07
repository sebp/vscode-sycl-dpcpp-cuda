FROM ghcr.io/sebp/dpcpp-sycl-cuda-container

USER root
RUN DEBIAN_FRONTEND=noninteractive \
    apt-get update \
    && apt-get install -y --no-install-recommends fish \
    && chsh -s $(which fish) vscode \
    && rm -fr /var/lib/apt/lists/*

ARG USERNAME=vscode

# Setup vscode extensions directory for non-root user
# see https://code.visualstudio.com/remote/advancedcontainers/avoid-extension-reinstalls
RUN mkdir -p /home/$USERNAME/.vscode-server/extensions \
    && chown -R $USERNAME /home/$USERNAME/.vscode-server \
    # Create /vscode directory as root to avoid permission denied error
    # when trying to create it as non-root
    && mkdir -p /vscode

USER $USERNAME