import threading
from tkinter import *
import json
import tkinter.scrolledtext as tkscrolled
import numpy as np

import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt; plt.rcdefaults()
from matplotlib.figure import Figure

with open("configuration.json", 'r+') as configuration_file:
    elasticsearch_directory = json.load(configuration_file)["elasticsearch_directory"]
    configuration_file.close()

import sys

sys.path.append(elasticsearch_directory)

try:
    from search_api import *
except:
    print("No Elasticsearch module found")
    exit(1)


class App(Frame):
    """
    This class contains the main functionality of the Kibana GUI.
    """

    class Constants():
        """
        This class contains the constants used in the GUI creation
        """
        START_OF_FILE = 1.0
        TOP_FRAME_HEIGHT = 50

    def __init__(self, master):
        """
        This parameter initializes the main App frame (and configures it) and calls the method to create
        all of the app widgets.
        :param master: Main Window
        """
        super().__init__()
        self.master = master
        self.figure = Figure()

        self.default_query = "16042018 http clientIP all size_response all ORDER clientIP"
        #self.default_query = "16042018 http clientIP all GROUP"
        #self.default_query = "16042018 http clientIP 131.174.154.24 size_response all COUNT"
        self.last_query = ""

        self.search_engine = Elasticsearch()

        self.has_been_just_launched = True
        self.createWidgets(self.master)

    def update_text_ui(self, original_logs, bottom):
        """
        This method updates the ScrollableText Widget that displays the logs that are a match with the query.

        :param original_logs: logs that are a match with the query
        :param bottom: ScrollableText widget that contains the logs
        :return: The function does not return anything.
        """

        new_text = "\n\n"
        log_counter = 0
        for log in original_logs:
            new_text += "Log number " + str(log_counter) + ": \n\n"
            log_counter += 1

            for key in log.keys():
                if str(log[key]) != "-":
                    new_text = new_text + key + ": " + str(log[key]) + "\n"

            new_text += "\n\n"

        bottom.config(state=NORMAL)
        bottom.delete(self.Constants.START_OF_FILE, END)
        bottom.insert(self.Constants.START_OF_FILE, new_text)
        bottom.config(state=DISABLED)

    def update_graphic_ui(self, query, top, results):
        """
        This method updates the Frame Widget that displays the graphic result.

        :param query: query performed
        :param top: frame that contains the graphic/s
        :param results: result of the query
        :return: The method does not return anything
        """

        split_query = query.split(" ")
        _, _, _, pairs, action = self.search_engine.getQueryInfo(elasticsearch_directory, split_query)

        if action == "COUNT":
            # Create graphic based on the result of the COUNT action result structure
            x_axis_title = ""
            for pair in pairs:
                x_axis_title += pair[0] + ": " + pair[1] + " "

            y_pos = np.arange(1)

            plt.rcdefaults()
            fig, ax = plt.subplots(figsize=(5, 1))

            ax.barh(results, results, align='center')
            ax.set_yticks(y_pos)
            ax.set_xlabel("Count - " + x_axis_title)
            ax.set_title('Query Results')

            fig.tight_layout()

            # Now we integrate the graphic with the Graphic UI
            self.figure = fig
            top.figure = self.figure
            top.draw()
            top.get_tk_widget().pack(side=TOP, fill=BOTH, expand=True)

        elif action == "GROUP":
            # Create graphic based on the result of the GROUP action result structure
            y_axis_name = "Count"

            results.keys()

            fig = plt.figure(figsize=(12, 3))
            s = fig.add_subplot(111)

            y_pos = np.arange(len(results.keys()))
            y_axis_values = []

            objects = []

            for key in results.keys():
                y_axis_values.append(results[key])
                objects.append(key)

            s.bar(y_pos, y_axis_values, align='center')
            plt.xticks(y_pos, objects)
            s.set_xticklabels(objects)
            s.set_ylabel(y_axis_name)
            s.set_title('Query Results')

            for ax in fig.axes:
                matplotlib.pyplot.sca(ax)
                plt.xticks(rotation=45)

            fig.tight_layout()

            # Now we integrate the graphic with the Graphic UI
            self.figure = fig
            top.figure = self.figure
            top.draw()
            top.get_tk_widget().pack(side=TOP, fill=BOTH, expand=True)

        elif action == "ORDER":
            # Create graphic based on the result of the ORDER action result structure

            # Check that the there are 2 field-value pairs in the query, just in case
            if len(pairs) == 2:
                fig, ax1 = plt.subplots(figsize=(12, 5))

                y_axis_name = "Count"
                objects = results.keys()
                y_pos = np.arange(len(objects))
                y_axis_values = []

                data = []
                for key in results.keys():
                    y_axis_values.append(results[key]["count"])
                    data.append(results[key][pairs[-1][0]])

                plt.bar(y_pos, y_axis_values, align='center')
                plt.xticks(y_pos, objects)
                plt.xticks(rotation=-90)
                plt.ylabel(y_axis_name)
                plt.title('Query Results')

                ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

                color = 'tab:red'
                ax2.set_ylabel([pairs[-1][0]], color=color)  # we already handled the x-label with ax1
                ax2.plot(objects, data, color=color)
                ax2.tick_params(axis='y', labelcolor=color)

                fig.tight_layout()  # otherwise the right y-label is slightly clipped

                # Now we integrate the graphic with the Graphic UI
                self.figure = fig
                top.figure = self.figure
                top.draw()
                top.get_tk_widget().pack(side=TOP, fill=BOTH, expand=True)
            else:
                pass

    def update_ui(self, top, bottom, original_logs, results, elasticsearch_directory, query):
        """
        This method updates the UI with the result of the query --graphic and text---.

        :param top: Frame that contains the graphic
        :param bottom: ScrollableText widget that contains the logs
        :param original_logs: logs that are a match with the query
        :param results: result of the query, that is the action performed over the logs that are a match with the
                        query.
        :param elasticsearch_directory:
        :return: This function does not return anything.
        """

        print("Updating UI in update_ui method")

        # Update Text UI in thread, so UI doesn't freeze
        new_text_thread = threading.Thread(
            target=self.update_text_ui(original_logs, bottom))
        new_text_thread.run()

        # Update Graphic UI in thread, so UI doesn't freeze
        new_graphic_thread = threading.Thread(
            target=self.update_graphic_ui(query, top,results))
        new_graphic_thread.run()

        print("Leaving update_ui method")

    def search(self, top, bottom, search, query=None):
        """
        This method is the bridge between the UI, the Elasticsearch API and the UI Updater

        :param top: Frame widget that contains the graphic
        :param bottom: ScrollableText widget that contains the logs that are a match with the query.
        :param search: SearchBar widget
        :param query: query that will be performed in the Elasticsearch API
        :return: this function does not return anything
        """

        print("Entering search method in Kibana GUI\n")

        with open("configuration.json", 'r+') as configuration_file:
            elasticsearch_directory = json.load(configuration_file)["elasticsearch_directory"]
            configuration_file.close()

        if query is not None:
            original_logs, results = self.search_engine.search(elasticsearch_directory, query)
        else:
            original_logs, results = self.search_engine.search(elasticsearch_directory, search.get())
            query = search.get()

        new_thread = threading.Thread(
            target=self.update_ui(top, bottom, original_logs, results, elasticsearch_directory, query))
        new_thread.run()

        print("Leaving search method in Kibana GUI")

    def createWidgets(self, master):
        """
        This method creates all of the Tkinter widgets that are part of the UI
        :param master: Main Window of the App, that will contain all the widgets created
        :return: The method does not return anything
        """

        with open("configuration.json", 'r+') as configuration_file:
            elasticsearch_directory = json.load(configuration_file)["elasticsearch_directory"]
            configuration_file.close()

        # Create all of the main containers
        dark_grey = '#898686'
        light_grey = '#c1c1c1'

        top_frame = Frame(master, bg=dark_grey, width=master.winfo_width(), height=self.Constants.TOP_FRAME_HEIGHT)
        center_bottom_frame = Frame(master, bg=light_grey, width=master.winfo_width())

        # layout all of the main containers
        master.grid_rowconfigure(1, weight=1)
        master.grid_columnconfigure(0, weight=1)

        top_frame.grid(row=0, sticky="ew")
        center_bottom_frame.grid(row=1, sticky="nsew")

        # create the center widgets
        center_bottom_frame.grid_rowconfigure(0, weight=1)
        center_bottom_frame.grid_columnconfigure(1, weight=1)

        ctr_bottom_left = Frame(center_bottom_frame, bg=dark_grey, width=254)
        ctr_bottom_mid_right = Frame(center_bottom_frame)
        ctr_bottom_mid_right_top = FigureCanvasTkAgg(self.figure, master=ctr_bottom_mid_right)
        ctr_bottom_mid_right_bottom = Frame(ctr_bottom_mid_right, bg="white")

        ctr_bottom_left.grid(row=0, column=0, sticky="ns")
        ctr_bottom_mid_right_top.draw()
        ctr_bottom_mid_right_top.get_tk_widget().pack(side=TOP, fill=BOTH, expand=True)
        ctr_bottom_mid_right.grid(row=0, column=1, sticky="nsew")
        ctr_bottom_mid_right_bottom.pack(fill=BOTH)

        # Create and configure the query result label (title)
        query_result_title = Label(ctr_bottom_mid_right_bottom)
        query_result_title.config(text="Logs that are a match with the query", font='Helvetica 14 bold',
                                  bg="white", width=164, anchor=W, justify=LEFT)
        query_result_title.grid(row=0, column=0)

        text_wrapper = Frame(ctr_bottom_mid_right_bottom)
        text_wrapper.config(height=500)
        text_wrapper.grid(row=1, column=0, sticky="nswe")

        bottom_text = tkscrolled.ScrolledText(text_wrapper, bg="white")
        bottom_text.grid(row=0)
        bottom_text['font'] = ('Helvetica', '12')

        # Create left panel label (title)
        left_label_title = Label(ctr_bottom_left)
        left_label_title.config(text="Available Indexes", bg="white", font='Helvetica 14 bold', width=32,
                                justify=LEFT)
        left_label_title.place(x=ctr_bottom_left.winfo_x(), y=ctr_bottom_left.winfo_y())

        # Create left panel list (body) and scrollbar
        available_indexes = self.search_engine.available_indexes(elasticsearch_directory)

        listbox = Listbox(ctr_bottom_left, bg="white", width=int(master.winfo_width()*0.025), height=500,
                          selectmode=MULTIPLE)
        listbox.place(x=left_label_title.winfo_x(), y=left_label_title.winfo_y() + 22)

        for i in range(0, len(available_indexes)):
            listbox.insert(i + 1, available_indexes[i])

        # Create and configure the search bar
        search_bar = Entry(top_frame, bg="white", text="Search Here", width=int(master.winfo_width()*0.1118))
        search_bar.grid(row=0, column=0)
        search_button = Button(top_frame, bg='white', text="Search", width=int(master.winfo_width()*0.01),
                               command=lambda top=ctr_bottom_mid_right_top, bottom=bottom_text,
                                              search=search_bar:
                                                self.search(top, bottom, search))
        search_button.grid(row=0, column=1)

        # When the UI is launched for the first time, we show a default query so that the UI is not empty.
        if self.has_been_just_launched:
            self.search(ctr_bottom_mid_right_top, bottom_text, search_bar, query=self.default_query)
            self.has_been_just_launched = False


if __name__ == "__main__":
    root = Tk()
    root.title("Log Management System v1")
    canvas = Canvas(root, width=2000, height=1000)
    canvas.pack()
    canvas.update()
    my_gui = App(canvas)
    my_gui.mainloop()