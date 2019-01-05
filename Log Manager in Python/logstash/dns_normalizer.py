import threading

from normalizer import *


class DNSNormalizer(threading.Thread, AbstractNormalizer):
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

        # foreach log file
        for file in logging_files:
            path = self.directory+file

            # open the file and get its lines
            with open(path) as logfile:
                lines = logfile.readlines()

                # foreach line on the file
                for line in lines:
                    split_line = (" ".join(line.split()).split(" "))
                    print(split_line)

                    date_split = split_line[0].split("/")
                    if len(date_split[0]) == 1:
                        timestamp = ['0'+date_split[0], date_split[1], date_split[2], split_line[1]]
                    if len(date_split[1]) == 1:
                        timestamp = [date_split[0], '0' + date_split[1], date_split[2], split_line[1]]
                    else:
                        timestamp = [date_split[0], date_split[1], date_split[2], split_line[1]]

                    protocol = split_line[6]
                    send_receive = split_line[7]
                    client_ip = split_line[8]
                    record_type = split_line[12]
                    flag = split_line[13][0:-1]
                    domain = split_line[14]

                    # create the dictionary that will be dumped into the json file
                    dic = {u"type": "dns", u"timestamp": timestamp, u"clientIP": client_ip, u"protocol": protocol, u"send_receive": send_receive, u"record_type": record_type, u"flag": flag, u"domain": domain}

                    # create a new entry in the root dictionary. Each new "log" have a unique id
                    info_to_dump["dns_" + str(id)] = dic

                    id += 1

        # dump all the files information into one same json file
        self.queue.put(info_to_dump)
        print("Leaving" + self.name)
