from django.contrib.auth.models import User
from django import forms

from django.contrib.auth import authenticate, login, logout
from django.core.paginator import Paginator
from django.views import View
from django.shortcuts import *
from iplapp.models import *



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


class Loginview(View):
    def get(self, request, *args, **kwargs):
        loginform= Loginform()
        return render(request, 'loginform.html', context={'form': loginform, 'link': 'signup'})

    def post(self,request,*args, **kwargs):
        loginform= Loginform()
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(request, username=username, password=password)
        if user is not None:
            login(request, user)
            return redirect('homepage')
        return render(request,'loginform.html', context={ 'form':loginform , 'link': 'signup', 'messages':'invalid request'})

def logout_view(request):
    logout(request)
    return redirect('login')


class Signupview(View):
    def get(self,request, *args, **kwargs):
        signupform = Signupform()
        return render(request, 'loginform.html', context={'form':signupform , 'link': 'login'})

    def post(self,request, *args, **kwargs):
        signupform = Signupform(request.POST)
        if signupform.is_valid():
            user = User.objects.create_user(**signupform.cleaned_data)
            user.save()
            login(request,user)
            return redirect('homepage')
        return render('login')
