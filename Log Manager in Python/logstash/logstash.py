import queue

from http_normalizer import *
from syslog_normalizer import *
from dns_normalizer import *
from constants import *

import datetime

import json


def thread_creator(log, directory, queue):
    """
    Create a new thread.
    Depending on the type of log we pass as parameter, a different type of thread
    will be created.

    :param log: type of log
    :param directory: directory of the log files
    :param queue: global queue
    :return: created thread
    """

    if log == Constants.HTTP:
        return HTTPNormalizer(log, "HTTP", log, directory, queue)
    elif log == Constants.SYSLOG:
        return SYSLOGNormalizer(log, "SYSLOG", log, directory, queue)
    else:
        return DNSNormalizer(log, "DNS", log, directory, queue)


def main():
    print("main code")

    logging_status = [False, False, False]
    logging_directories = ["", "", ""]

    # Read configuration file in JSON
    with open('configuration.json') as data_file:
        configuration = json.load(data_file)

    # Update configuration data arrays and variables
    logging_status[Constants.SYSLOG] = configuration["syslog"]["active"]
    logging_directories[Constants.SYSLOG] = configuration["syslog"]["directory"]
    logging_status[Constants.HTTP] = configuration["http"]["active"]
    logging_directories[Constants.HTTP] = configuration["http"]["directory"]
    logging_status[Constants.DNS] = configuration["dns"]["active"]
    logging_directories[Constants.DNS] = configuration["dns"]["directory"]
    elasticsearch_directory = configuration["elasticsearch"]["directory"]

    # Create new threads and put them on a list
    thread_list = []

    dict_queue = queue.Queue()

    for i in range(0, Constants.TYPES_OF_LOGS):
        # if the log type is active, we create a new thread to normalize its data
        if logging_status[i]:
            thread_list.append(thread_creator(i, logging_directories[i], dict_queue))

    # Start all the threads
    for t in thread_list:
        t.start()

    # Wait for all the threads to finish
    for t in thread_list:
        t.join()

    json_dictionaries = []

    for i in range(0, dict_queue.qsize()):
        json_dictionaries.append(dict_queue.get())

    # We create a new JSON file with all the logs in JSON format
    # To do so, first we need to merge all the partial dictionaries into a new one
    info_to_dump = {}
    if len(json_dictionaries) == 4:
        info_to_dump = {**json_dictionaries[0], **json_dictionaries[1], **json_dictionaries[2], **json_dictionaries[3]}
    elif len(json_dictionaries) == 3:
        info_to_dump = {**json_dictionaries[0], **json_dictionaries[1], **json_dictionaries[2]}
    elif len(json_dictionaries) == 2:
        info_to_dump = {**json_dictionaries[0], **json_dictionaries[1]}
    elif len(json_dictionaries) == 1:
        info_to_dump = json_dictionaries[0]

    # Now we dump the merged dictionaries into the new JSON file
    print(info_to_dump)

    with open(elasticsearch_directory + "logs.json", 'r+') as outfile:
        json.dump(info_to_dump, outfile)

    print('Main Finished...')


if __name__ == "__main__":
    main()