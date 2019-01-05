import threading

from normalizer import *


class HTTPNormalizer(threading.Thread, AbstractNormalizer):
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
                    split_line = line.split(" ")
                    http_log_elements = []
                    separated = ''
                    end_of_separated_element_found = True

                    # we split all the elements in the file
                    for element in split_line:
                        if (element.startswith('"') and element.endswith('"')) or \
                                (element.startswith('[') and element.endswith(']')):
                            http_log_elements.append(element)
                        elif element.startswith('"') or element.startswith('['):
                            separated += (" " + element)
                            end_of_separated_element_found = False
                        elif element.endswith('"') or element.endswith(']'):
                            separated += (" " + element)
                            http_log_elements.append(separated)
                            end_of_separated_element_found = True
                            separated = ''
                        elif not end_of_separated_element_found:
                            separated += (" " + element)

                            if split_line[-1] == element:
                                http_log_elements.append(separated)
                        else:
                            http_log_elements.append(element)

                    # We separate the time information in submodules: day, month, year, time and timezone
                    time_array = []
                    provisional_time_array = http_log_elements[3].split("/")
                    time_array.append(provisional_time_array[0][1:])
                    time_array.append(provisional_time_array[1])
                    provisional_time_array = provisional_time_array[2].split(":")
                    time_array.append(provisional_time_array[0])
                    time_array.append(provisional_time_array[1]+":"+provisional_time_array[2]+":"+provisional_time_array[3].split(" ")[0])

                    # create the dictionary that will be dumped into the json file
                    dic = {u"type": "http", u"clientIP": http_log_elements[0], u"identity": http_log_elements[1], u"username": http_log_elements[2], u"timestamp": time_array, u"request": http_log_elements[4], u"status_code": http_log_elements[5], u"size_response": http_log_elements[6], u"url": http_log_elements[7], u"useragent": http_log_elements[8]}

                    # create a new entry in the root dictionary. Each new "log" have a unique id
                    info_to_dump["http_"+str(id)] = dic

                    id += 1

        # dump all the files information into one same json file
        self.queue.put(info_to_dump)
        print("Leaving" + self.name)
