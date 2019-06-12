from django import forms


class Loginform(forms.Form):
    username= forms.CharField(
        required= True,
        max_length=32,
        widget=forms.TextInput(attrs={'class':'input', 'placeholder': 'enter username'})
    )

    password=forms.CharField(
        required=True,
        max_length=64,
        widget= forms.PasswordInput(attrs={'class':'input', 'placeholder':'enter password'})
    )

class Signupform(forms.Form):
    first_name = forms.CharField(
        required=True,
        max_length=32,
        widget=forms.TextInput(attrs={'class':'input', 'placeholder':'enter fistname'})
    )

    last_name = forms.CharField(
        required=True,
        max_length=32,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'enter lastname'})
    )
    username = forms.CharField(
        required=True,
        max_length=32,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'enter username'})
    )
    password= forms.CharField(
        required=True,
        max_length=32,
        widget=forms.PasswordInput(attrs={'class': 'input', 'placeholder': 'enter password'})
    )