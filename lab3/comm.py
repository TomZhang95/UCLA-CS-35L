#!/usr/bin/python
import sys, string, locale
from optparse import OptionParser

class comm:
        def __init__(self,filename1, filename2):
                if filename1 == "-":
                        f1 = sys.stdin
                else:
                        f1 = open(filename1, 'r')
                self.lines1 = f1.read().splitlines()
                f1.close()
                if filename2 == "-":
                        f2 = sys.stdin
                else:
                        f2 = open(filename2, 'r')
                self.lines2 = f2.read().splitlines()
                f2.close()
        def readlines1(self):
                return self.lines1
        def readlines2(self):
                return self.lines2

def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Outputs Differences between FILE1 and FILE2."""

    parser = OptionParser(version=version_msg, usage=usage_msg)

    parser.add_option("-1",
                    action="store_true", dest="hide1",
                    default=False,
                    help="suppress column 1")

    parser.add_option("-2",
                    action="store_true", dest="hide2",
                    default=False,
                    help="suppress column 2")

    parser.add_option("-3",
                    action="store_true", dest="hideComm",
                    default=False,
                    help="suppress common column")

    parser.add_option("-u",
                    action="store_true", dest="unsorted",
                    default=False,
                    help="compatible with unsorted file")

    options, args = parser.parse_args(sys.argv[1:])
    if len(args) != 2:
            parser.error("wrong number of operands give")

    Matrix = [["               " for col in range(3)] for row in range(100000)]

    input_file1 = args[0]
    input_file2 = args[1]

    try:
            build = comm(input_file1, input_file2)
    except IOError as e:
            parser.error("I/O error({0}): {1}".
                         format(e.errno, e.sterror))
    file1 = build.readlines1()
    file2 = build.readlines2()

    unique = 0
    rows1 = 0

    for temp1 in file1:
            for temp2 in file2:
                    if temp1 == temp2:
                            Matrix[rows1][2]=temp1
                            unique = 1
            if unique == 0:
                    Matrix[rows1][0]=temp1
            unique = 0
            rows1+=1

    unique = 0
    rows2 = 0
    for temp2 in file2:
            for temp1 in file1:
                    if temp2 == temp1:
                            unique = 1
            if unique == 0:
                    Matrix[rows2][1]=temp2
            unique=0
            rows2+=1

    rows = 0
    if rows1 > rows2:
            rows = rows1
    else:
            rows = rows2

    if options.unsorted == 1:
            for i in range (rows):
                    if Matrix[i][0]\
!= "               ":
                            sys.\
stdout.write(Matrix[i][0]+'\n')
            for i in range (rows):
                    if Matrix[i][2]\
!= "               ":
                            sys.\
stdout.write("               "+\
             "               "+Matrix[i][2]+'\n')
            for i in range (rows):
                    if Matrix[i][1]\
!= "               ":
                            sys.\
stdout.write("               "+Matrix[i][1]+'\n')
    else:
            if options.hide1 == 0:
                if options.hide2 == 0:
                    if options.hideComm == 0:
                            for i in range (rows):
                                    sys.\
stdout.write(Matrix[i][0]+\
Matrix[i][1]+\
Matrix[i][2]+'\n')
                    else:
                            for i in range (rows):
                                        if Matrix[i][0]\
!= "               " or \
                                            Matrix[i][1]\
!= "               ":
                                                sys.\
stdout.write(Matrix[i][0]+Matrix[i][1]+'\n')
                else:
                        if options.hideComm == 0:
                                for i in range (rows):
                                        if Matrix[i][0]\
!= "               " \
                                            or Matrix[i][2]\
!= "               ":
                                                sys.\
stdout.write(Matrix[i][0]+Matrix[i][2]+'\n')
                        else:
                                for i in range (rows):
                                        if Matrix[i][0]\
!= "               ":
                                                sys.\
stdout.write(Matrix[i][0]+'\n')
            else:
                if options.hide2 == 0:
                        if options.hideComm == 0:
                                for i in range (rows):
                                        if Matrix[i][1]\
!= "               " \
                                            or Matrix[i][2]\
!= "               ":
                                                sys.\
stdout.write(Matrix[i][1]+Matrix[i][2]+'\n')
                        else:
                                for i in range (rows):
                                        if Matrix[i][1]\
!= "               ":
                                                sys.\
stdout.write(Matrix[i][1]+'\n')
                else:
                        if options.hideComm == 0:
                                for i in range (rows):
                                        if Matrix[i][2]\
!= "               ":
                                                sys.\
stdout.write(Matrix[i][2]+'\n')


if __name__ == "__main__":
        main()

