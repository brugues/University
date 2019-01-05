import threading

from normalizer import *

from pyparsing import Word, alphas, Suppress, Combine, nums, string, Optional, Regex
from time import strftime


class Parser(object):
    """
    The parser class
    """

    def __init__(self):
        ints = Word(nums)

        # priority
        # priority = Suppress("<") + ints + Suppress(">")

        # timestamp
        month = Word(string.ascii_uppercase, string.ascii_lowercase, exact=3)
        day = ints
        hour = Combine(ints + ":" + ints + ":" + ints)

        timestamp = month + day + hour

        # hostname
        hostname = Word(alphas + nums + "_" + "-" + ".")

        # appname
        appname = Word(alphas + "/" + "-" + "_" + ".") + Optional(Suppress("[") + ints + Suppress("]")) + Suppress(":")

        # message
        message = Regex(".*")

        # pattern build
        self.__pattern = timestamp + hostname + appname + message

    def parse(self, line):
        parsed = self.__pattern.parseString(line)

        payload = {}
        # payload["priority"] = parsed[0]
        # time_array = [split_line[1], split_line[0], datetime.datetime.now().year, split_line[2]]
        payload["timestamp"] = strftime("%Y-%m-%d %H:%M:%S")
        # print(payload['timestamp'])
        payload["hostname"] = parsed[3]
        # print(payload['hostname'])
        payload["appname"] = parsed[4]
        # print(payload['appname'])
        # payload["pid"] = parsed[5]
        # print(payload["pid"])
        payload["message"] = parsed[5]
        # print(payload["message"])

        return payload


class SYSLOGNormalizer(threading.Thread, AbstractNormalizer):
    """

    """

    def __init__(self, thread_id, name, counter, directory, queue):
        threading.Thread.__init__(self)
        self.threadID = thread_id
        self.name = name
        self.counter = counter
        self.directory = directory
        self.queue = queue

    def run(self):
        print("Starting " + self.name)

        logging_files = self.getLogFilesFromDirectory()

        # dictionary that will be dumped into the JSON file
        info_to_dump = {}
        id = 0

        # open the file and get its lines
        for file in logging_files:
            path = self.directory + file

            parser = Parser()

            # open the file and get its lines
            with open(path) as logfile:
                lines = logfile.readlines()

                # foreach line on the file
                for line in lines:
                    try:
                        dic = parser.parse(line)
                        dic['type'] = 'syslog'
                        info_to_dump["syslog_"+str(id)] = dic
                        id += 1
                    except:
                        print("error")

        self.queue.put(info_to_dump)
        print("Leaving" + self.name)
