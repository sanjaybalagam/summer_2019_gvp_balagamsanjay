from onlineapp.models import *
from django import forms



class Marksform(forms.ModelForm):
    class Meta:
        model=MockTest1
        exclude=['total','student']
        widgets={
            'problem1': forms.NumberInput(attrs={'class':'input', 'placeholder':'enter problem1 marks' }),
            'problem2':forms.NumberInput(attrs={'class':'input', 'placeholder':'enter problem2 marks' }),
            'problem3':forms.NumberInput( attrs={'class':'input', 'placeholder':'enter problem3 marks'} ),
            'problem4': forms.NumberInput( attrs={'class': 'input', 'placeholder':'enter problem4 marks'}),
        }


