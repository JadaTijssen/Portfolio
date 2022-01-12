# This program returns the current weather description of a requested place.

import requests

def get_weather(city):
    api_key = "6259067ceac0680e898834ae9b3e9835"
    url = "http://api.openweathermap.org/data/2.5/weather?q=" \
          + city + "&appid=" + api_key + "&units=metric"

    request = requests.get(url)
    json = request.json()

    if json.get('message') == 'city not found':
        return "city not found"

    description = json.get("weather")[0].get("description")
    temp_min = json.get("main")["temp_min"]
    temp_max = json.get("main")["temp_max"]
    temp_feel = json.get("main")["feels_like"]

    return {'temp_min': temp_min,
            'temp_max': temp_max,
            'temp_feel': temp_feel,
            'description': description}

def main():
    city = input("What place do you want to get the weather of?\n")
    weather_dict = get_weather(city)

    if weather_dict == "city not found":
        print("This city is not part of the OpenWeatherMap database.")
        return

    min = weather_dict.get('temp_min')
    max = weather_dict.get('temp_max')
    feel = weather_dict.get('temp_feel')
    description = weather_dict.get('description')

    print("For " + city + ", today's forecast is " + description + ".")
    print("The minimal temperature is:", min, "degrees Celcius.")
    print("The maximal temperature is:", max, "degrees Celcius.")

    if feel > max:
        print("But don't worry, it feels like", feel, "degrees Celcius.")
    elif feel >= min:
        print("It feels like", feel, "degrees Celcius.")
    else:
        print("But I'm sorry, it feels like", feel, "degrees Celcius.")

main()