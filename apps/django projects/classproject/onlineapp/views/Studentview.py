from django.views import View
from django.shortcuts import *
from django.contrib.auth.mixins import LoginRequiredMixin
from onlineapp.forms.marks import *
from onlineapp.forms.student import *
from django.urls import *
from django.contrib.auth.mixins import LoginRequiredMixin


class Addstudent(LoginRequiredMixin, View):
    login_url = '/onlineapp/login/'
    def get(self, request , *args, **kwargs):
        form1 , form2 =None, None
        print('post method')
        if 'pk2' in kwargs:
            print('pk2 in kwargs')
            student=Student.objects.get(pk=kwargs.get('pk2'))
            marks= MockTest1.objects.get(student__id= student.id)
            form1= Addstudentform(instance=student)
            form2= Marksform(instance= marks)
        else:
            form1 = Addstudentform()
            form2 = Marksform()
        return render(request, template_name='addstudent.html' , context={'form1': form1, 'form2':form2 ,'title':'Add new students'} )


    def post(self,request,*args, **kwargs):

        if 'pk2' in kwargs:
            if resolve(request.path_info).url_name == 'deletestudent':
                Student.objects.get(pk=kwargs.get('pk2')).delete()
                return redirect('colleges')

            if resolve(request.path_info).url_name == 'editstudent':
                studentins= Student.objects.get(pk=kwargs.get('pk2'))
                marksins=MockTest1.objects.get(student=studentins.id)

                studentform = Addstudentform(request.POST, instance='studentins')
                marksform = Marksform(request.POST, instance='marksins')

                k = studentform.save(commit=False)
                k.college = College.objects.get(pk=kwargs.get('pk1'))
                k.save()

                m = marksform.save(commit=False)
                m.student = k
                m.total = m.problem1 + m.problem2 + m.problem3 + m.problem4
                m.save()

                return redirect('colleges')

        studentform = Addstudentform(request.POST)
        marksform = Marksform(request.POST)
        if studentform.is_valid() and marksform.is_valid():
            k=studentform.save(commit=False)
            k.college= College.objects.get(pk=kwargs.get('pk1'))
            k.save()

            m=marksform.save(commit=False)
            m.student= k
            m.total= m.problem1 +m.problem2 + m.problem3 + m.problem4
            m.save()

            return redirect('colleges')
        return render(request, template_name='addcollege.html', context={ 'form1': studentform,'form2':marksform ,
                                                                          'title': 'Add new college'})
