#!/bin/sh

protoc --python_out=. --proto_path=. alpha.proto
protoc --python_out=. --proto_path=. beta.proto
protoc --python_out=. --proto_path=. gamma.proto
protoc --python_out=. --proto_path=. step1.proto
protoc --python_out=. --proto_path=. step2.proto
protoc --python_out=. --proto_path=. step3.proto