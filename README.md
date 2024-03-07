# Billboard Data Analysis Program
## This GitHub repository contains a C++ program designed to analyze and extract insights from Billboard chart data spanning from 1960 to 2020. The program allows users to interact with Billboard data, offering various analytical functionalities to explore trends, artist performances, and song popularity over the decades.

### Features
Data Import: The program reads Billboard chart data from CSV files, handling different time spans (1960-1980, 1981-2000, 2001-2020).
Data Structures: Utilizes structs to represent dates and billboard data, facilitating organized data management.
Analysis Functions: Includes functions to analyze data, such as identifying songs with the most number one occurrences, longest-lasting songs on charts, songs with the greatest weekly climb, and artist-specific searches.
Interactive Menu: An interactive menu allows users to select different types of analyses, including overall data insights, specific decade/year analysis, and artist search functionality.
User Input: Supports user input for selecting data files, time frames, and search queries, enhancing the program's interactivity and usability.

### How It Works
1. Welcome Message: Displays an introductory message explaining the program's purpose.
2. File Selection: Users can choose which dataset to analyze based on three time spans.
3. Reading Data: The program reads the selected CSV file and stores the data in a vector of BillboardData structs.
4. Menu Options: Users can choose from various options to analyze the data, including:
   - Displaying overall data information.
   - Analyzing songs with the most number one occurrences in a specific decade or year.
   - Identifying the song with the longest duration on the charts for a selected time frame.
   - Finding the song with the greatest weekly climb within a given decade or year.
   - Performing a search by artist name to find songs that reached number one.
5. Analysis Results: Based on the selected menu option, the program displays relevant analysis results, providing insights into the Billboard data.

