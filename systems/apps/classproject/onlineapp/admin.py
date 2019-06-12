from django.contrib import admin

# Register your models here.
from .models import *
admin.site.register(College)
admin.site.register(Teacher)
admin.site.register(MockTest1)
admin.site.register(Student)
