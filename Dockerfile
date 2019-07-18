FROM alpine:3.9

ENV CXX="g++ -std=c++98"

# Install geos
RUN apk --update add --virtual .geos-deps \
        which \
        make \
        gcc \
        g++ \
        file \
        git \
        autoconf \
        automake \
        libtool && \
    cd /tmp && \
    git clone https://git.osgeo.org/gitea/geos/geos.git geos && \
    cd geos && \
    git checkout 3.7.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make check && \
    make install && \
    cd / && \
    apk del .geos-deps && \
    rm -rf /tmp/* && \
    rm -rf /user/local/man

# install CGAL
RUN apk --update add --virtual .cgal-deps \
        which \
        make \
        cmake \
        gcc \
        g++ \
        eigen-dev \
        boost-dev \
        gmp-dev \
        mpfr-dev \
        zlib-dev && \
    cd /tmp && \
    wget https://github.com/CGAL/cgal/releases/download/releases%2FCGAL-4.13.1/CGAL-4.13.1.tar.xz && \
    tar xf CGAL-4.13.1.tar.xz && \
    rm -f CGAL-4.13.1.tar.xz && \
    cd CGAL-4.13.1 && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DWITH_Eigen3=ON .. && \
    make && \
    make install && \
    cp lib/* /usr/local/lib && \
    cd / && \
    apk del .cgal-deps && \
    rm -rf /tmp/* && \
    rm -rf /user/local/man

# install val3dity
RUN apk --update add --virtual .val3dity-deps \
        make \
        cmake \
        gcc \
        g++ \
        boost-dev \
        eigen-dev \
        gmp-dev \
        mpfr-dev \
        python3 \
        pytest \
        py-yaml \
        py-lxml \
        py3-setuptools && \
    cd /tmp && \
    wget https://github.com/tudelft3d/val3dity/archive/2.1.1.tar.gz && \
    tar xzf 2.1.1.tar.gz && \
    rm -f 2.1.1.tar.gz && \
    cd val3dity-2.1.1 && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd .. &&\
    ls -ls . && \
    val3dity data/cityjson/cube.json && \
    python3 -m pytest --runfull && \
    apk del .val3dity-deps && \
    cd / && \
    apk --update add \
        make \
        gcc \
        g++ \
        boost \
        eigen \
        gmp \
        bash \
        mpfr3 && \
    rm -rf /tmp/* && \
    rm -rf /user/local/man

RUN mkdir /data && \
    chown 1001 /data && \
    chgrp 0 /data && \
    chmod g=u /data && \
    chgrp 0 /etc/passwd && \
    chmod g=u /etc/passwd
    
RUN val3dity --version

USER 1001

COPY --chown=1001:0 uid_entrypoint.sh /usr/local/bin/

WORKDIR /data

ENTRYPOINT ["/usr/local/bin/uid_entrypoint.sh"]

CMD ["--version"]
