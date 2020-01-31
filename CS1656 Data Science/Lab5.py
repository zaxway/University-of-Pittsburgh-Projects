import json
from datetime import datetime, timedelta, date
import requests
import pandas as pd
import matplotlib.pyplot as plt


wprdc_api_endpoint = "https://data.wprdc.org/api/3/action/datastore_search_sql"

# id for database table
resource_id = "1a1329e2-418c-4bd3-af2c-cc334e7559af"

# Get the date from 9 months ago)
start_date = datetime.now() - timedelta(days=270)

# Convert to a string the format the the data center accepts (yyyy-mm-dd)
start_str = start_date.strftime("%Y-%m-%d")

# SQL query we'll use in API call to request data
query = """
SELECT *
FROM "{}"
WHERE "INSPECT_DT" >= '{}' AND "CITY" = '{}' """.format(resource_id, start_str, "Pittsburgh")

# Make WPRDC API Call
response = requests.get(wprdc_api_endpoint, {'sql': query})

# Parse response JSON into python dictionary
response_data = json.loads(response.text)
#print(response_data)

# Convert dictionary to dataframe
df = pd.DataFrame.from_dict(response_data['result']['records'])

# Print the number of rows
print(df.shape[0], "rows total")

df.head()

query = """
SELECT DISTINCT "DESCRIPTION_NEW"
FROM "{}"
WHERE "INSPECT_DT" >= '{}' AND "CITY" = '{}' """.format(resource_id, start_str, "Pittsburgh")

response = requests.get(wprdc_api_endpoint, {'sql': query})

df = pd.DataFrame.from_dict(json.loads(response.text)['result']['records'])


query = """
SELECT "FACILITY_NAME", COUNT("DESCRIPTION_NEW")
FROM "{}"
WHERE "INSPECT_DT" >= '{}' AND "CITY" = '{}' AND "RATING" <> '{}'
GROUP BY "FACILITY_NAME" """.format(resource_id, start_str, "Pittsburgh", "V")

response = requests.get(wprdc_api_endpoint, {'sql': query})

df = pd.DataFrame.from_dict(json.loads(response.text)['result']['records'])
