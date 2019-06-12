from onlineapp.views.Collegeview import *
from onlineapp.views.Studentview import *
from onlineapp.views.loginview import *
from onlineapp.views.rest_api import *

urlpatterns = [
  #  path('',homepage),
    path('logout',logout_view, name='logout'),
    path('get_colleges/',CollegeView.as_view(), name='colleges' ),
    path(r'login/', Loginview.as_view(), name='login'),
    path('signup', Signupview.as_view(), name='signup'),
    path('get_colleges/<int:pk>',CollegeView.as_view()),
    path('get_colleges/<int:pk>/edit',Addcollege.as_view(), name='editcollege'),
    path('get_colleges/<int:pk>/delete', Addcollege.as_view(), name='deletecollege'),
    path('addcollege/', Addcollege.as_view()),
    path('get_colleges/<int:pk1>/addstudent',Addstudent.as_view(), name='addstudent'),
    path('get_colleges/<int:pk1>/<int:pk2>/edit', Addstudent.as_view(), name='editstudent'),
    path('get_colleges/<int:pk1>/<int:pk2>/delete', Addstudent.as_view(), name='deletestudent'),



    # rest urls
    path('v1/colleges', college_api, name='rest_colleges'),
    path('v1/colleges/<int:id>',college_api, name='rest_college'),


    path('v1/colleges/<int:cpk>/students', StudentsList.as_view(), name='rest_students'),
    path('v1/colleges/<int:cpk>/students/<int:spk>', StudentDetails.as_view(), name='rest_student_details')
    #    path('college_student_info/<int:id>/' , get_student_info  ),

]