#!/usr/bin/perl

use strict;
use warnings;

# NOTE: REGEX CANNOT MATCH PARENS!

my $file = 'test.txt';
open my $info, $file or die "could not open $file: $!";

my $i = 1;

while( my $line = <$info>) {
    print("". $line ."\n");

    # remove spaces and tabs
    $line =~ s/[ \t]//g;
    # remove parens, because regex cannot match parens :(
    $line =~ s/[()]//g;
    # remove newline
    $line =~ s/\n//g;
    # my $match = $line =~ m/^([a-zA-Z]+=)?([a-zA-Z]+|[0-9]+)([*]([a-zA-Z]+|[0-9]+))*([+\-]([a-zA-Z]+|[0-9]+)([*]([a-zA-Z]+|[0-9]+))*)*$/;
    my $match = $line =~  m/^\d?[a-z]+(\d+((:\d+((-\d+)?|(,\d+)?)(;\d+)?)|(,\d+))?)?([a-z]+)?$/i;
    
    # (-\d+)?|(,\d+)?) gives verse -13 or ,13
    if($match) {
        print("Line " . $i . " is correct\n");
    } else {
        print("Syntax error detected on line " . $i . "\n");
    }
    $i = $i + 1;
}


