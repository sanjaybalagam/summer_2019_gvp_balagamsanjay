from onlineapp.models import *
from django import forms



class Addstudentform(forms.ModelForm):
    class Meta:
        model=Student
        exclude=['id','dob','college']
        widgets={
            'name': forms.TextInput(attrs={'class':'input', 'placeholder':'enter name' }),
            'email':forms.TextInput(attrs={'class':'input', 'placeholder':'enter location' }),
            'db_folder':forms.TextInput(attrs={'class':'input', 'placeholder':'enter dbfolder'}),
            'dropped_out':forms.CheckboxInput(  ),
        }


