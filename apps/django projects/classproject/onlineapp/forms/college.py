from onlineapp.models import College
from django import forms

class Addcollegeform(forms.ModelForm):
    class Meta:
        model=College
        exclude=['id']
        widgets={
            'name': forms.TextInput(attrs={'class':'input', 'placeholder':'enter name' }),
            'location':forms.TextInput(attrs={'class':'input', 'placeholder':'enter location' }),
            'acronym': forms.TextInput(attrs={'class':'input', 'placeholder':'enter acronym' }),
            'contact': forms.EmailInput(attrs={'class':'input', 'placeholder':'enter contact' }),
        }


