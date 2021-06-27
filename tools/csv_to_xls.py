import csv
import openpyxl

wb = openpyxl.Workbook()
ws = wb.active

csvfile=input("Input CSV File Path:")
xlsxfile=input("Input Xlsx File Path:")

with open(csvfile) as f:
    reader = csv.reader(f, delimiter=',')
    for row in reader:
        ws.append(row)

wb.save(xlsxfile)