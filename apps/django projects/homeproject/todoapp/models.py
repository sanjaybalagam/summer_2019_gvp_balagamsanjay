from django.db import models

# Create your models here.

class TodoList(models.Model):
    name=models.CharField(max_length=20)
    created=models.DateTimeField(auto_now=True)


    def __str__(self):
        return self.name

class TodoItem(models.Model):
    description=models.CharField(max_length=128)
    due_date= models.DateField()
    completed = models.BooleanField()

    todolist = models.ForeignKey(TodoList, on_delete=models.CASCADE)  #

    def __str__(self):
        return self.description

