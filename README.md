# CirKit Addon for PLiM

This addon implements some code based on logic synthesis for the PLiM computer.  In a [CirKit](https://msoeken.github.io/cirkit.html) installation, you need to do the following to enable this plugin.  From the CirKit base path enter

    cd addons
    git clone https://github.com/msoeken/cirkit-addon-plim.git
    cd ..
    cmake -Denable_cirkit-addon-plim=ON build
    make -C build cirkit

## References

 * Mathias Soeken, Pierre-Emmanuel Gaillardon, and Giovanni De Micheli: [RM3 based logic synthesis](https://msoeken.github.io/publications.html#c85), ISCAS 2017.
