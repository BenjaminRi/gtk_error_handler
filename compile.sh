#!/bin/bash

gcc `pkg-config --cflags gtk+-3.0` -o gtk_error_handler gtk_error_handler.c `pkg-config --libs gtk+-3.0`

