# /bin/sh

mkdir /tmp/data
cd /tmp/data
wget -c https://storage.googleapis.com/cvdf-datasets/mnist/train-images-idx3-ubyte.gz
wget -c https://storage.googleapis.com/cvdf-datasets/mnist/train-labels-idx1-ubyte.gz
wget -c https://storage.googleapis.com/cvdf-datasets/mnist/t10k-images-idx3-ubyte.gz
wget -c https://storage.googleapis.com/cvdf-datasets/mnist/t10k-labels-idx1-ubyte.gz
