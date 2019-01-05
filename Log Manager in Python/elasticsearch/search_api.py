import json


class Elasticsearch:
    """
    This class contains all the required functionality to search through the log indexes.
    """

    class Constants:
        """

        """
        pass

    def __init__(self):
        """

        """
        self.months = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']

    def getQueryInfo(self, elastic_directory, split_query):
        """
        This method returns analyzes the split query and returns the fields.

        :param elastic_directory: directory where the elasticsearch resides
        :param split_query: query to be analyzed.
        :return: Information of the query that is needed for other methods in order to perform the query.
        """

        # We get the types of logs that are permitted.
        with open(elastic_directory + "configuration.json", 'r+') as configuration_file:
            types_logs_permitted = json.load(configuration_file)["types_logs"]
            configuration_file.close()

        # Get the diferent types of field for each possible type of log.
        types_field = {}
        for log in types_logs_permitted:
            with open(elastic_directory + "configuration.json", 'r+') as configuration_file:
                types_field[str(log)] = json.load(configuration_file)[str(log)]
                configuration_file.close()

        number_of_field_value_pairs = int((len(split_query) - 3)/2)

        # Obtain the different pairs of FIELD-VALUE that are present in the query.
        index = 2
        pairs = []
        for i in range(0, number_of_field_value_pairs * 2 - 1, 2):
            pairs.append([split_query[index + i], split_query[index + i + 1]])

        # Check if the action parameter is the last or second to last in the list.
        action_is_last_field = True
        for type in types_field.keys():
            if split_query[-1] in types_field[type]:
                action_is_last_field = False

        if action_is_last_field:
            action = split_query[-1]
        else:
            action = split_query[-2]

        # Return all the values obtained.
        return types_logs_permitted, types_field, split_query[0], pairs, action

    def isQueryValid(self, elastic_directory, split_query):
        """
        This method checks if the given query if valid, and thus results can be obtained.

        :param elastic_directory: directory where the elasticsearch resides
        :param split_query: query that needs to be checked, already been split in components.
        :return: True if the query is valid. False if it is not.
        """

        if len(split_query) < 5:
            return False

        types_logs_permitted, types_field, timestamp, pairs, action = self.getQueryInfo(elastic_directory, split_query)

        # Query does not have enough parameters or wrong number of parameters.
        if action == "ORDER":
            modulus = 1
            if len(pairs) > 2:
                return False
        else:
            modulus = 0

        # Check if the query has the wrong length
        if len(split_query) % 2 == modulus:
            return False
        elif action == "GROUP" and len(pairs) > 1:
            return False

        # Check if timestamp is valid.
        if len(timestamp) != 8:
            return False
        elif int(timestamp[0:2]) < 0 or int(timestamp[0:2]) > 31:
            return False
        elif timestamp[2:4] not in self.months:
            return False

        types_logs_query = split_query[1]
        types_logs_query = types_logs_query.split(",")

        # Check if the type of logs are valid.
        for type in types_logs_query:
            if type not in types_logs_permitted:
                if type != 'all':
                    return False

        # Check if all the fields in the query are valid.
        for key in types_field.keys():
            if key in types_logs_query:
                for pair in pairs:
                    if pair[0] not in types_field[key]:
                        return False

        # Check if, in case the case is order, all the fields that are not ordered can be added, i.e. are ints.
        if action == "ORDER":
            all_not_action_fields_are_int = True
            for pair in pairs:
                try:
                    if pair[0] != split_query[-1]:
                        number = int(pair[1])
                except Exception:
                    if pair[1] != "all":
                        all_not_action_fields_are_int = False
            if not all_not_action_fields_are_int:
                return False

        # The query is correct, so we can return True.
        return True

    def getResults(self, elastic_directory, split_query):
        """
        This method gets the logs that match the query.

        :param elastic_directory: directory where the elasticsearch resides
        :param split_query: query made by the user, already separated by fields.
        :return: A dictionary with all the logs that.
        """

        print("Entering getResults method")

        _, _, timestamp, pairs, _ = self.getQueryInfo(elastic_directory, split_query)

        # Get the list of indexes that can be analyzed for the query.
        with open(elastic_directory + "timestamps.json", 'r+') as timestamps_file:
            indexes = json.load(timestamps_file)["timestamps"]
            timestamps_file.close()

        # Check if the selected timestamp has been indexed. If not, we can't perform the query, so None is returned.
        if timestamp not in indexes:
            print("Any results found: Timestamp has not been indexed")
            print("Exiting getResults method")
            return None
        else:
            # Timestamp valid. We can continue looking for results.
            query_matches = {}
            original_logs = []

            with open(elastic_directory + "indexes/" + timestamp + ".json", "r+") as index_file:
                logs = json.load(index_file)
                index_file.close()

            for log in logs:
                log_match_info = {}
                match = 0
                for pair in pairs:
                    # print(pair[0]) ==== FIELD
                    # print(pair[1]) ==== VALUE
                    if pair[1] == "all" or pair[1] == logs[log][pair[0]]:
                        log_match_info[pair[0]] = logs[log][pair[0]]
                        match += 1
                if match == len(pairs):
                    query_matches[log] = log_match_info
                    original_logs.append(logs[log])

        print(query_matches)
        print("Exiting getResults method with some results\n")
        return original_logs, query_matches

    def performAction(self, elastic_directory, split_query, results):
        """
        This method performs the given operation by the user to the results obtained in the getResults() method.

        :param elastic_directory: directory where the elasticsearch resides
        :param results: matches obtained in the getResults() method.
        :param split_query: query already split in parts into a list
        :return: final result of the query.
        """

        print("Entering performAction method")
        _, _, _, pairs, action = self.getQueryInfo(elastic_directory, split_query)

        # Perform action accordingly with user's input
        if action == "COUNT":
            print("Leaving performAction method\n")
            return len(results)

        elif action == "GROUP":
            count = {}
            fields = []

            # Count how many types each field appears in the results.
            for key in results.keys():
                if results[key][pairs[0][0]] in fields:
                    count[results[key][pairs[0][0]]] += 1
                else:
                    count[results[key][pairs[0][0]]] = 1
                    fields.append(results[key][pairs[0][0]])
            print(count)
            print("Exiting performAction method with results\n")
            return count

        elif action == "ORDER":
            count = {}
            fields = []

            # Count how many times each field appears in the results, plus all other fields in the query are
            # added.
            for key in results.keys():
                if results[key][pairs[0][0]] in fields:
                    for pair in pairs:
                        if pair[0] == split_query[-1]:
                            count[results[key][pairs[0][0]]]['count'] += 1
                        else:
                            count[results[key][pairs[0][0]]][pair[0]] += int(results[key][pair[0]])
                else:
                    partial_count = {}
                    for pair in pairs:
                        if pair[0] == split_query[-1]:
                            partial_count['count'] = 1
                        else:
                            partial_count[pair[0]] = int(results[key][pair[0]])
                    count[results[key][pairs[0][0]]] = partial_count
                    fields.append(results[key][pairs[0][0]])

            print(count)
            print("Exiting performAction method with results\n")
            return count

        # In case, for some reason, the isQueryValid() method didn't work, make sure the action is valid, return None.
        else:
            print("Exiting performAction method without results\n")
            return None

    def search(self, elastic_directory, query):
        """
        This method handles all the necessary operations to perform the query entered by the user. By doing so,
        it calls methods to ensure that the query is valid and obtain the desired results.

        :param elastic_directory: directory where the elasticsearch resides
        :param query: query that is going to be performed.
        :return: result of the query
        """

        split_query = query.split(" ")

        if self.isQueryValid(elastic_directory, split_query):
            original_logs, result = self.getResults(elastic_directory, split_query)

            if result is None:
                return "We did not find any matches", None
            else:
                action_result = self.performAction(elastic_directory, split_query, result)

                if action_result is None:
                    return "Your action could not be performed", None
                else:
                    return original_logs, action_result
        else:
            return "Query is not Valid", None

    def available_indexes(self, elasticsearch_directory):
        """
        This method checks the timestamps that are already indexed and available for search.

        :param elasticsearch_directory: directory where the elasticsearch resides
        :return: the list with the indexed timestamps
        """

        # We get the available indexes from the timestamps.json file
        with open(elasticsearch_directory + "timestamps.json", 'r+') as timestamps_file:
            indexes_available = json.load(timestamps_file)["timestamps"]
            timestamps_file.close()

        return indexes_available


if __name__ == "__main__":
    query = "16042018 http clientIP all GROUP clientIP"
    directory = "/Users/Josep/Documents/GitHub/log-gestor/elasticsearch/"

    Elasticsearch = Elasticsearch()
    indexes = Elasticsearch.available_indexes(directory)
    results = Elasticsearch.search(directory, query)
    print(results)
