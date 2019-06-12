from django.views import View
from django.shortcuts import *
from django.contrib.auth import authenticate, login, logout
from onlineapp.forms.loginform import *
from django.contrib import messages
from django.contrib.auth.models import User

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
            return redirect('colleges')
        return render(request,'login', context={ 'form':loginform , 'link': 'signup', 'messages':'invalid request'})

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
            return redirect('colleges')
        return render('login')
