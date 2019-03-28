#!/bin/bash
modprobe vcan
ip link add dev vcan type vcan
ip link set up vcan
