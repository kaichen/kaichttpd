#!/bin/bash

if [ ! -e httpd ]
then make
fi

./httpd

