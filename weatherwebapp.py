import tkinter as tk
import pandas as pd #import pandas package
from tkinter import font
import requests

Height = 500
Width = 600


def format_weather(weather):
    final=" "
    try:
        name = weather['name']
        desc = weather['weather'][0]['description']
        temp = weather['main']['temp']
        feelslike = weather['main']['feels_like']
        final = 'City: %s \n Conditions: %s \nTemperature in Farh: %s\n Feels Like:%s' %(name,desc,temp, feelslike)
    except:
        final = "There was probelem on city entry try a new city or check spelling"
    return final




def get_weather(city):
    weather_key='ea2d2301208c3ee5cc51a7fc4d8eb7c7'
    url='https://api.openweathermap.org/data/2.5/weather'
    params = {'APPID': weather_key, 'q': city, 'units': 'Imperial'}
    response = requests.get(url, params=params)
    df = pd.read_csv('WeatherSearch.csv')
    weather = response.json()
    print(response.json())
    print(weather['name'])
    print(weather['weather'][0]['description'])
    print(f"Ground Temperature {weather['main']['temp']}")
    print(f"Feels like {weather['main']['feels_like']}")
    label['text']=format_weather(weather)


root = tk.Tk()

canvas = tk.Canvas(root, height=Height, width=Width)
canvas.pack()

background_image = tk.PhotoImage(file='landscape.png')
background_label = tk.Label(root, image=background_image)
background_label.place(relheight=1, relwidth=1)

frame = tk.Frame(root, bg='#80c1ff', bd=5)
frame.place(relx=0.5, rely=0.1, relwidth=0.75, relheight=0.1, anchor='n')

entry = tk.Entry(frame, font=('Courier', 14))
entry.place(relwidth=0.65, relheight=1)

button = tk.Button(frame, text="Weather", font=('Courier', 12), command=lambda: get_weather(entry.get()))
button.place(relx=0.7, relwidth=0.3, relheight=1)

lowe_frame = tk.Frame(root, bg='#80c1ff', bd=5)
lowe_frame.place(relx=0.5, rely=0.25, relwidth=0.75, relheight=0.6, anchor='n')

label = tk.Label(lowe_frame, bg="White")
label.place(relwidth=1, relheight=1)

root.mainloop()
