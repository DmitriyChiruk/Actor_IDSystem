Preequirements:
1) Go to Edit->Project Settings->Maps & Modes->Default GameMode and select Actor_IdentifierGameModeBase. 
2) Go to Edit->Project Settings->Maps & Modes->Game Instance Class and select IDSystemInstance. 

	This make possible for UIDSystemInstance Save() and Load() to work. As well it allows system to save 
it`s instance to the file. (*Temporary problem: not loading saved data*)

Here is a brief instruction how to mark Actors for identification:
1) Create an Actor
2) Add IDSystem component to it
3) Set ID and select Identified Checkbox if neded

Note: ID 0 will process as unmarked for Identification and won`t be shown.