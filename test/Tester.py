# In The Name Of God
# ========================================
# [] File Name : Tester.py
#
# [] Creation Date : 22-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
__author__ = 'Parham Alvani'

import socket
import argparse
import cmd


class FirstPlayer(cmd.Cmd):
    def __init__(self, sck):
        self.sck = sck
        cmd.Cmd.__init__(self)
        cmd.Cmd.prompt = "(OpenTrax Tester) "

    def do_move(self, arg):
        move = arg
        move += '\n'
        self.sck.send(bytes(move, 'ASCII'), 0)
        move = ''
        while True:
            c = sck.recv(1, 0)
            move += str(c)
            if c == b'\n':
                break
        print(move)

    def do_quit(self, arg):
        return True


class SecondPlayer(cmd.Cmd):
    def __init__(self, sck):
        self.sck = sck
        cmd.Cmd.__init__(self)
        cmd.Cmd.prompt = "(OpenTrax Tester) "

    def do_move(self, arg):
        move = ''
        while True:
            c = sck.recv(1, 0)
            move += str(c)
            if c == b'\n':
                break
        print(move)

        move = arg
        move += '\n'
        self.sck.send(bytes(move, 'ASCII'), 0)

    def do_quit(self, arg):
        return True


if __name__ == '__main__':
    parser = argparse.ArgumentParser("OpenTrax NetServer Player Tester")
    parser.add_argument('--ip-address', dest='ip', help='Trax game server ip address', default='127.0.0.1', type=str)
    parser.add_argument('--player', dest='player', choices=['first', 'second'], default='second',
                        help='Trax game player number')
    parser.add_argument('--port', dest='port', help='Trax game port number', default=1373, type=int)
    args = parser.parse_args()

    sck = 0
    try:
        sck = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sck.connect((args.ip, args.port))
    except ConnectionError as e:
        print(e.args[1] + " on " + args.ip + " : " + str(args.port))
        quit(1)

    if args.player == 'first':
        FirstPlayer(sck).cmdloop("OpenTrax NetServer Player Tester <First Player>")

    if args.player == 'second':
        SecondPlayer(sck).cmdloop("OpenTrax NetServer Player Tester <Second Player")