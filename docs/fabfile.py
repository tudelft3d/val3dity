from __future__ import with_statement
from fabric.api import *
from fabric.contrib.project import rsync_project

env.gateway = 'linux-bastion-ex.tudelft.nl'
env.user = 'hledoux'
env.hosts = ['geovalidation.bk.tudelft.nl']


def deploy():
    local("make dirhtml")
    remotedir = '/var/www/val3dity_docs/'
    rsync_project(local_dir='./_build/dirhtml/', 
                  remote_dir=remotedir,
                  delete=True)
