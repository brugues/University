from abc import ABC, abstractmethod
import os


class AbstractNormalizer(ABC):
    """
    This class is the Abstract class for the Normalizers, and contains the common methods
    """

    """
        This method gets all the log files that are in the directory found in the configuration file.
    """
    def getLogFilesFromDirectory(self):
        files_in_logging_directory = os.listdir(self.directory)

        logging_files = []

        for file in files_in_logging_directory:
            extension = os.path.splitext(file)[1]
            if extension == ".log":
                logging_files.append(file)

        return logging_files