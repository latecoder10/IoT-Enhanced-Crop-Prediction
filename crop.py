from tkinter import *
import pandas as pd
from sklearn.tree import DecisionTreeClassifier

# load the dataset
crop_data = pd.read_csv("crop_data.csv")

# separate the features and target variable
X = crop_data.iloc[:, :-1] # features
y = crop_data.iloc[:, -1] # target variable

# create a decision tree classifier model
dt_model = DecisionTreeClassifier(random_state=99)

# train the model on the data
dt_model.fit(X, y)

# create a Tkinter window
root = Tk()
root.title("Crop Prediction")

# create labels and entry fields for each input feature
temp_label = Label(root, text="Temperature:")
temp_label.grid(row=0, column=0)
temp_entry = Entry(root)
temp_entry.grid(row=0, column=1)

humid_label = Label(root, text="Humidity:")
humid_label.grid(row=1, column=0)
humid_entry = Entry(root)
humid_entry.grid(row=1, column=1)

soil_moist_label = Label(root, text="Soil Moisture:")
soil_moist_label.grid(row=2, column=0)
soil_moist_entry = Entry(root)
soil_moist_entry.grid(row=2, column=1)

soil_cond_label = Label(root, text="Soil Conductivity:")
soil_cond_label.grid(row=3, column=0)
soil_cond_entry = Entry(root)
soil_cond_entry.grid(row=3, column=1)

water_level_label = Label(root, text="Water Level:")
water_level_label.grid(row=4, column=0)
water_level_entry = Entry(root)
water_level_entry.grid(row=4, column=1)

# create a function to predict the crop
def predict_crop():
    # get input values from the user
    temp = float(temp_entry.get())
    humid = float(humid_entry.get())
    soil_moist = float(soil_moist_entry.get())
    soil_cond = float(soil_cond_entry.get())
    water_level = float(water_level_entry.get())
    
    # make a prediction with the model
    new_data = pd.DataFrame({'Temperature': [temp], 'Humidity': [humid], 'Soil Moisture': [soil_moist], 'Soil Conductivity': [soil_cond], 'Water Level': [water_level]})
    prediction = dt_model.predict(new_data)

    # display the predicted crop
    result_label.configure(text="Predicted crop: " + prediction[0])
    if temp < 10  :
        result_label.configure(text="Predicted crop: " + "Crop production not suitable in this climate condition")
    if temp > 50  :
        result_label.configure(text="Predicted crop: " + "Crop production not suitable in this climate condition")
    if humid < 10 :
        result_label.configure(text="Predicted crop: " + "Crop production not suitable in this climate condition")
    if humid > 100 :
        result_label.configure(text="Predicted crop: " + "Crop production not suitable in this climate condition")
    if soil_moist > 5 :
        result_label.configure(text="Predicted crop: " + "Crop production not suitable in this climate condition")
    if soil_cond  > 3 :
        result_label.configure(text="Predicted crop: " + "Crop production not suitable in this climate condition")
   

# create a button to predict the crop
predict_button = Button(root, text="Predict Crop", command=predict_crop)
predict_button.grid(row=5, column=1)

# create a label to display the predicted crop
result_label = Label(root)
result_label.grid(row=6, column=1)

# run the Tkinter event loop
root.mainloop()
