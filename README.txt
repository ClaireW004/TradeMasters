The TradeMasters program attempts to provide the user with an easy
way to quickly view all trade for a single good between a chosen importer and
all the countries that the importer receives the goods from. By using the program,
a user who may be interested in trade data between countries can specify a good and importing
country and see a list of all countries that export that good to the importer.

The trade data in this program comes from the CEPII BACI Database (https://www.cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37),
which is a comprehensive international trade database.
We're using the HS22 classification, meaning all data corresponds to trade flows from the year 2022.

How to use it:

Required Files
Ensure you have access to the following files before using the tool:

product_codes_HS22_V202401b.csv
    Contains a list of approximately 6000 HS 6-digit product codes.
country_codes_V202401b.csv
    Includes all countries as per the CEPII source.
BACI_HS22_Y2022_V202401b_final.csv
    Holds all the trade data for the year 2022. This file is essential for retrieving trade flow information.

How to Use the Tool
1. Choose a Data Structure
    On starting the tool, you will be prompted to select the data structure for processing:

    Enter 1 for Adjacency List
    Enter 2 for Adjacency Matrix

2. Enter a Product Code
    Next, input the HS 6-digit product code for the good you are interested in.
    Check product_codes_HS22_V202401b.csv for valid product codes.

3. Specify the Importing Country
    Type the name of the importing country you want data for.
    Use country_codes_V202401b.csv to ensure proper spelling and formatting (please input country name, NOT the code.)
    Mismatched names will result in the prompt to input the correct country name.


4. View Results
    The tool will display trade values from various exporting countries to the selected importing country,
    sorted in asceding order (weight/cost of trade), from top to bottom.
    Data is sourced from BACI_HS22_Y2022_V202401b_final.csv.

5. Make Further Selections
    After viewing the results, you can:
    0: Choose a different importing country for the same product
    1: Exit the program.

Thank you for using TradeMasters!