import os
import os.path
import csv

PATH_DATABASE = '/etc/eletrohorse-database/'
DATABASE_NAME = '/database/'

class DataBase:
    def __init__(self):
        self.file_database_name = "config.csv"

    def create(self):
        path_name = os.getcwd() + DATABASE_NAME
        if not os.path.isdir(path_name):
            os.mkdir(path_name)
        return path_name
    
    def writer(self, header, data, filename, option):
        with open (filename, "w", newline = "") as csvfile:
            if option == "write":
                movies = csv.writer(csvfile)
                movies.writerow(header)
                for x in data:
                    movies.writerow(x)
            elif option == "update":
                writer = csv.DictWriter(csvfile, fieldnames = header)
                writer.writeheader()
                writer.writerows(data)
                print()
                print("Data updated successfully!")
            else:
                print("Option is not known")

    def file_create(self):
        with open(self.create() + self.file_database_name, 'w', newline='') as csvfile:
            fieldnames = ['ID', 'Program', 'TempMax', 'TempMin', 'Time', 'PWM']
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerow(
                {'ID': 1, 'Program': 'TERMO', 'TempMax': 54, 'TempMin': 30, 'Time': 25, 'PWM': 1})
            writer.writerow(
                {'ID': 2, 'Program': 'CRIO', 'TempMax': 7, 'TempMin': 4, 'Time': 25, 'PWM': 1})

    def file_read(self, key):
        data = []
        with open(self.create() + self.file_database_name, newline= "") as csvfile:
            reader = [row for row in csv.DictReader(csvfile)]
            for row in reader:
                if row.get('Program') == key:
                    data.append(int(row.get('TempMax')))
                    data.append(int(row.get('TempMin')))
                    data.append(int(row.get('Time')))
                    data.append(int(row.get('PWM')))
                    data.append(row.get('Program'))

        return data
        
    def file_update(self, key, tempmax, tempmin, time, pwm):
        idx = -1
        with open(self.create() + self.file_database_name, newline= "") as csvfile:
            reader = [row for row in csv.DictReader(csvfile)]
            for row in reader:
                idx = idx + 1
                if row.get('Program') == key:
                    reader[idx]['TempMax'] = tempmax
                    reader[idx]['TempMin'] = tempmin
                    reader[idx]['Time'] = time
                    reader[idx]['PWM'] = pwm
                    
                    readerHead = reader[idx].keys()
                    self.writer(readerHead, reader, self.create() + self.file_database_name, "update")      
