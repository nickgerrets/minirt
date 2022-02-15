#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    make_sources.sh                                    :+:    :+:             #
#                                                      +:+                     #
#    By: ngerrets <ngerrets@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/20 17:29:20 by ngerrets      #+#    #+#                  #
#    Updated: 2021/09/20 17:29:21 by ngerrets      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

echo -n "SOURCES :=" > sources.mk ;
find src -type f -name *.c | awk '{print "	" $0 " \\"}' >> sources.mk ;

echo -n "HEADERS :=" > headers.mk ;
find include -type f -name *.h | awk '{print "	" $0 " \\"}' >> headers.mk ;
