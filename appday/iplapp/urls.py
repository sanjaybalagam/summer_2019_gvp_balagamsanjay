from iplapp.views.viewsv1 import *
from django.urls import path, include
from iplapp.views.loginviews import *
from iplapp.views.pointstableview import *
from iplapp.views.team_home import *


urlpatterns = [
    path('',homepage, name="homepage"),
    path('<int:year>/',homepage, name='homepage1'),
    path('match/<int:id>',match_details , name='matches'),
    path(r'login', Loginview.as_view(), name='login'),
    path('signup', Signupview.as_view(), name='signup'),
    path('logout', logout_view, name='logout'),
    path('pointstable/<int:year>',pointstable ,name='pointstable_int'),
    path('pointstable/',pointstable, name='pointstable'),
    path('season/',team_home_page, name='team_home_page' ),
    path('season/<int:year>/team_home_page/<str:team>',team_home_page,name='team_home_page_str')
]