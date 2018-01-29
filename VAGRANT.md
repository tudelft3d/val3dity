# Installing Vagrant

To download Vagrant for supported platforms, see [here](https://www.vagrantup.com/downloads.html)

# Installing VirtualBox

If choosing VirtualBox as your virtualization provider, see [here](https://www.virtualbox.org/wiki/Downloads).

You may have to enable hardware virtualization extensions in your BIOS before using it.

If running on Ubuntu, you may have to install a newer version of VirtualBox than what is available in the public repositories in order for it to work correctly with Vagrant.

# Setting up val3dity with Vagrant & VirtualBox
Once Vagrant has been installed, you can start an environment by checking out the val3dity code, then changing to the directory which contains the Vagrantfile by typing:

    # Windows users will need to uncomment the line ending configuration option.
    git clone git@github.com:tudelft3d/val3dity.git val3dity #--config core.autocrlf=input
    cd val3dity
    vagrant up

# Other Virtualization Providers

If you would like to use Parallels instead of VirtualBox, please run the following command:
```
vagrant up --provider=parallels
```
Please note that this requires the Parallels Vagrant plugin, which can be installed:
```
vagrant plugin install vagrant-parallels
```

Similarly, if you would like to use VMware Workstation instead of VirtualBox, please run the following command:
```
vagrant up --provider vmware_workstation
```
Please note that this requires the VMware Vagrant plugin, which can be installed:
```
vagrant plugin install vagrant-vmware-workstation
```

# Vagrant Provisioning

The initialization of the vagrant vm (`vagrant up`) will take about an hour at first.

You should be able to log into the running VM by typing:

    vagrant ssh

Within this login shell, you can build the code, run the server or the tests. For example, to run the tests:

```
    vagrant ssh
    cd ~/val3dity_build
    cmake ../val3dity
    make
    make install
```

The val3dity root folder (on host) is mapped to the `/home/vagrant/val3dity` folder on the guest. Note that # Vagrant shared folders (e.g. `/home/vagrant/val3dity`) incur a heavy performance penalty within the virtual machine when there is heavy I/O, so they should only be used for source files. Any compilation step, database files, and so on should be done outside the shared folder filesystem inside the guest filesystem itself.

**Acknowledgement**
The majority of this description was taken from the [Hootenanny project](https://github.com/ngageoint/hootenanny/blob/master/VAGRANT.md)
