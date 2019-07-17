#!/bin/bash -ex

docker login --username ${DOCKER_USERNAME} --password ${DOCKER_PASSWORD}

if [ "${TRAVIS_EVENT_TYPE}" = "cron" ]
then
    docker push cheesecakeman/val3dity:latest
fi

if [ "${TRAVIS_TAG}" != "" ]
then
    docker tag cheesecakeman/val3dity:latest cheesecakeman/val3dity:${TRAVIS_TAG}
    docker push cheesecakeman/val3dity:${TRAVIS_TAG}
fi