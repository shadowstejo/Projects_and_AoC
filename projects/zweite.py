with open('hannover.txt',"r",encoding="utf-8") as f:
    words = f.read().replace("Ü","UE").replace("ü","UE").replace("Ö","OE").replace("ö","OE").replace("Ä","AE").replace("ä","AE").split()
    vorschlag = ["BEDRAENGTERFLOH","ABENDERSTERORGIE","HALTCHERIE","BLAEHUNGHOBFRED","FRANKOKNEBELN","SCHREIEUNDKOMIK","FANVERWEHTZUZUG","BOHRDOCHHAEUSER","SALZINSELNSTOPPEN","STERNBEGONIE","HAUSBLIEBOHNESTREIFEN","DERWEIDENBAUMDERIRRE","EILIGERELAUS","HEBELUMGRENZENTURM","DAFALZTMANNINHANNOVER","KEUSCHHEITIMORT","KORBINOST",]
    sort = ['ABDEEEFGHLNORRT', 'ABDEEEEGINORRRST', 'ACEEHHILRT', 'ABBDEEFGHHLNORU', 'ABEEFKKLNNNOR', 'CDEEHIIKKMNORSU', 'AEEFGHNRTUUVWZZ', 'ABCDEEHHHOORRSU', 'AEEILLNNNOPPSSSTZ', 'BEEEGINNORST', 'ABBEEEEFHHIILNNORSSTU', 'ABDDDEEEEEIIMNRRRRUW', 'AEEEGIILLRSU', 'BEEEEGHLMMNNRRTUUZ', 'AAAADEFHILMNNNNNORTVZ', 'CEEHHIIKMORSTTU', 'BIKNOORST']
    auswahl = []

    for word in words:
        if len(word) >= 9:
            auswahl.append("".join(word.upper()))
    for i in sort:
        for j in auswahl:
            if i == "".join(sorted(j)):
                print(i,j)

                
#'ACDEEEGHIIIKNR',    
        
