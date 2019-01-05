import json
import os
import time
import datetime
import dateutil.parser

from time import strptime


def indexer(elasticsearch_directory):
    """

    :return: no return for this class
    """

    # Keep indexing files until we break the loop
    while True:
        # if no logs are in the file, we can't index anything, so we leave the method
        if os.stat("logs.json").st_size == 0:
            break
        else:
            with open("timestamps.json", 'r+') as timestamps_file:
                old_timestamps = json.load(timestamps_file)['timestamps']
                timestamps_file.truncate(0)
                timestamps_file.close()

            with open("logs.json", 'r+') as data_file:
                logs = json.load(data_file)
                # We have loaded all the data in memory, so we can empty the file and close it
                data_file.truncate(0)
                data_file.close()

            # We iterate all over the logs dictionary to analyze all the timestamps in order and put the logs in the
            # correct index
            new_timestamps_string = []
            old_timestamps_new_logs = []

            new_timestamps_added = False
            timestamps_list_dictionaries = []
            map = {}
            number_of_timestamps_analysed = 0

            for log in logs:
                day = logs[log]["timestamp"][0]
                if len(str(day)) == 1:
                    day = '0' + str(day)

                if len(logs[log]["timestamp"][1]) == 1:
                    month = logs[log]["timestamp"][1]
                else:
                    month = strptime(logs[log]["timestamp"][1], '%b').tm_mon
                    if len(str(month)) == 1:
                        month = '0' + str(month)
                year = logs[log]["timestamp"][2]

                if logs[log]["type"] == "dns":
                    log_timestamp = day + str(month) + year
                else:
                    log_timestamp = day[1:]+str(month)+year

                # If we already have that timestamp, we need to add the log in that index. If not, we need to
                # create a new index.
                if str(log_timestamp) in old_timestamps:
                    if log_timestamp not in map.keys():
                        old_timestamps_new_logs.append(log_timestamp)

                        with open(elasticsearch_directory + "indexes/"+log_timestamp+".json", 'r+') as log_data:
                            data = json.load(log_data)
                            log_data.truncate(0)
                            log_data.close()

                        timestamps_list_dictionaries.append(data)
                        map[str(log_timestamp)] = number_of_timestamps_analysed
                        number_of_timestamps_analysed += 1

                    timestamps_list_dictionaries[map[str(log_timestamp)]][str(log)] = logs[log]

                # Create new index
                else:
                    new_timestamps_added = True

                    if log_timestamp not in map.keys():
                        map[str(log_timestamp)] = number_of_timestamps_analysed
                        number_of_timestamps_analysed += 1
                        timestamps_list_dictionaries.append({})

                    if log_timestamp not in new_timestamps_string:
                        new_timestamps_string.append(log_timestamp)

                    timestamps_list_dictionaries[map[str(log_timestamp)]][str(log)] = logs[log]

            for timestamp in new_timestamps_string:
                old_timestamps.append(timestamp)

            # Update the timestamps in the JSON file
            if new_timestamps_added:
                with open("timestamps.json", 'r+') as timestamps_file:
                    json.dump({"timestamps": old_timestamps}, timestamps_file)
                    timestamps_file.close()

            for timestamp in old_timestamps:
                print(timestamp in new_timestamps_string)
                if timestamp in old_timestamps_new_logs:
                    with open(elasticsearch_directory + "indexes/" + timestamp + ".json", "r+") as timestamp_file:
                        json.dump(timestamps_list_dictionaries[map[str(timestamp)]], timestamp_file)
                        timestamp_file.close()
                elif timestamp in new_timestamps_string:
                    print(timestamp)
                    with open(elasticsearch_directory + "indexes/" + timestamp + ".json", "w") as timestamp_file:
                        json.dump(timestamps_list_dictionaries[map[str(timestamp)]], timestamp_file)
                        timestamp_file.close()




def check_indexes(elasticsearch_directory):
    """

    :param elasticsearch_directory:
    :return:
    """

    with open("timestamps.json", 'r+') as timestamps_file:
        timestamps = json.load(timestamps_file)['timestamps']
        timestamps_file.close()

    for timestamp in timestamps:
        timestamp_day = timestamp[0:2]
        timestamp_month = timestamp[2:4]
        timestamp_year = timestamp[4:]

        if timestamp_month[0] == '0':
            timestamp_month = timestamp_month[-1]
        if timestamp_day[0] == '0':
            timestamp_day = timestamp_day[-1]

        insertion_date = dateutil.parser.parse(str(timestamp_month) + '.' + str(timestamp_day) + '.' + str(timestamp_year))
        right_now_30_days_ago = datetime.datetime.today() - datetime.timedelta(days=30)

        #if insertion_date > right_now_30_days_ago:
            # delete the index
            #os.remove(elasticsearch_directory+"indexes/"+timestamp+".json")


def indexer_controller():
    """
    This class controls the moment that the Elasticsearch model needs to index the logs
    :return: no return for this class
    """

    with open("configuration.json", 'r+') as configuration_file:
        elasticsearch_directory = json.load(configuration_file)["directory"]

    while True:
        print("Checking if any index needs to be deleted")
        check_indexes(elasticsearch_directory)
        print("Initialising indexer")
        indexer(elasticsearch_directory)
        print("Finished Indexing")
        print("Waiting 30 seconds")
        # Wait 30 minute until we index again
        time.sleep(30)


if __name__ == "__main__":
    indexer_controller()
