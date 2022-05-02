from django.db import models

# Create your models here.
class Books(models.Model):
    title           = models.CharField(max_length=50)
    author          = models.CharField(max_length=50)
    date            = models.DateField('date')
