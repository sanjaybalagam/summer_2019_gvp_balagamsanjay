from django.views import View
from django.shortcuts import *
from django.contrib.auth.mixins import LoginRequiredMixin
from onlineapp.forms.college import *
from django.urls import *


class CollegeView(LoginRequiredMixin,View):
    login_url = '/onlineapp/login/'
    def get(self, request , *args, **kwargs):
        if kwargs:
            college=get_object_or_404(College, **kwargs)
            students= list(college.student_set.order_by("-mocktest1__total"))
            return render(request, template_name='list_students.html', context={ 'college': college ,
                                                                                 'students': students,
                                                                                 'title': 'students from {}'.format(college.acronym),
                        'permissions': request.user.get_all_permissions()})
        colleges=College.objects.all()

        return render(request,template_name='list_colleges.html',context={'colleges': colleges , 'title': ' collegeslist'})


class Addcollege(LoginRequiredMixin, View):
    login_url = '/onlineapp/login/'
    def get(self, request , *args, **kwargs):
        get_form=None
        if kwargs:
            college=College.objects.get(**kwargs)
            get_form= Addcollegeform(instance=college)
        else:
            get_form = Addcollegeform()

        return render(request, template_name='addcollege.html' , context={'form': get_form ,'title':'Add new college|mentor app'} )

    def post(self,request,*args, **kwargs):
        if kwargs:
            if resolve(request.path_info).url_name == 'deletecollege':
                College.objects.get(**kwargs).delete()
                return redirect('colleges')

            if resolve(request.path_info).url_name == 'editcollege':
                clg = College.objects.get(**kwargs)
                form =  Addcollegeform(request.POST, instance=clg)
                if form.is_valid():
                    form.save()
                    return redirect('colleges')
        form = Addcollegeform(request.POST)
        if form.is_valid():
            form.save()
            return HttpResponseRedirect('/onlineapp/addcollege')
        return render(request, template_name='addcollege.html', context={ 'form': form, 'title': 'Add new college'})
