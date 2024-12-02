IDENTIFICATION DIVISION.
       PROGRAM-ID. ReconcileLists.

       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
           SELECT InputFile ASSIGN TO 'inputd1.txt'
               ORGANIZATION IS LINE SEQUENTIAL.

       DATA DIVISION.
       FILE SECTION.
       FD  InputFile.
       01  InputRecord.
           05  LeftNum  PIC 9(2).
           05  FILLER   PIC X(1).
           05  RightNum PIC 9(2).

       WORKING-STORAGE SECTION.
       01  EOF-FLAG       PIC X VALUE 'N'.
           88  EOF         VALUE 'Y'.
           88  NotEOF      VALUE 'N'.
       01  LeftArray.
           05  LeftNums OCCURS 100 TIMES PIC 9(2) VALUE ZEROS.
       01  RightArray.
           05  RightNums OCCURS 100 TIMES PIC 9(2) VALUE ZEROS.
       01  ArrayIdx      PIC 9(2) VALUE 1.
       01  DispIdx       PIC 9(2).
       01  TempNum       PIC 9(2).
       01  TotalDiff     PIC 9(4) VALUE 0.
       01  Diff          PIC 9(2).

       PROCEDURE DIVISION.
       MainSection.
           PERFORM OpenFile
           PERFORM ReadAndStoreData UNTIL EOF
           PERFORM SortData
           PERFORM CalcDiffs
           PERFORM DispResults
           PERFORM CloseFile
           GOBACK.

       OpenFile.
           OPEN INPUT InputFile
           MOVE 'N' TO EOF-FLAG
           .

       ReadAndStoreData.
           READ InputFile INTO InputRecord
               AT END
                   MOVE 'Y' TO EOF-FLAG
               NOT AT END
                   MOVE LeftNum TO LeftNums(ArrayIdx)
                   MOVE RightNum TO RightNums(ArrayIdx)
                   ADD 1 TO ArrayIdx
           .

       SortData.
           PERFORM VARYING DispIdx FROM 1 BY 1 UNTIL DispIdx = ArrayIdx - 1
               PERFORM VARYING TempNum FROM 1 BY 1 UNTIL TempNum = 
               ArrayIdx - DispIdx
                   IF LeftNums(TempNum) > LeftNums(TempNum + 1)
                       MOVE LeftNums(TempNum) TO TempNum
                       MOVE LeftNums(TempNum + 1) TO LeftNums(TempNum)
                       MOVE TempNum TO LeftNums(TempNum + 1)
                   END-IF
                   IF RightNums(TempNum) > RightNums(TempNum + 1)
                       MOVE RightNums(TempNum) TO TempNum
                       MOVE RightNums(TempNum + 1) TO RightNums(TempNum)
                       MOVE TempNum TO RightNums(TempNum + 1)
                   END-IF
               END-PERFORM
           END-PERFORM
           .

       CalcDiffs.
           MOVE 0 TO TotalDiff
           PERFORM VARYING DispIdx FROM 1 BY 1 UNTIL DispIdx = ArrayIdx
               COMPUTE Diff = FUNCTION ABS(LeftNums(DispIdx) - 
               RightNums(DispIdx))
               ADD Diff TO TotalDiff
           END-PERFORM
           .

       DispResults.
           DISPLAY 'Left List: '
           PERFORM VARYING DispIdx FROM 1 BY 1 UNTIL DispIdx >= ArrayIdx
               IF LeftNums(DispIdx) = 0
                   EXIT PERFORM
               END-IF
               DISPLAY LeftNums(DispIdx)
           END-PERFORM

           DISPLAY 'Right List: '
           MOVE 1 TO DispIdx
           PERFORM VARYING DispIdx FROM 1 BY 1 UNTIL DispIdx >= ArrayIdx
               IF RightNums(DispIdx) = 0
                   EXIT PERFORM
               END-IF
               DISPLAY RightNums(DispIdx)
           END-PERFORM

           DISPLAY 'Total Difference: ' TotalDiff
           .

       CloseFile.
           CLOSE InputFile
           .
