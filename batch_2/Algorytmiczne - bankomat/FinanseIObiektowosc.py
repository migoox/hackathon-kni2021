from openpyxl import Workbook

with open("faktura_do_zad_Python_15.10_21.00.csv", "r", encoding="utf-8") as faktura:
    fakturaTable = faktura.readlines()
    newFakturaTable = []
    wb = Workbook()
    sheet = wb.active
    sheet.append(("Nazwa Produktu", "Cena netto", "Podatek Vat", "Narzut","Cena Sklepowa"))

    for i, line in enumerate(fakturaTable):
        line = line.split(";")
        line[3] = line[3].rstrip()

        cena = round((int(line[1]) * 0.01)*(1+int(line[2])*0.01)*(1+int(line[3])*0.01),2)
        sheet.append((line[0],line[1],str(line[2])+"%",str(line[3])+"%",cena))

    wb.save("finanseIObiektowosc.xlsx")

