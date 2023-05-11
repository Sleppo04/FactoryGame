# FactoryGame


# Coding Guidelines
## Function Design
Functions are to be named according to PascalCase  
Functions shall have their corresponding object as the last part of their name
Examples:  
`CreateBuffer`  
`ReadBuffer`

Functions that have a pointer return value shall return NULL to indicate an error  
All functions shall accept a pointer to an integer as their last argument to supply error codes

## Variable naming
All variables, including struct members, shall follow the camelCase naming convention  
Examples:  
`dataStart`  
`allocatedLength`
