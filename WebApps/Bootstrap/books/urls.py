from django.urls import path, include
from .views import index, add, get, edit, update, delete

urlpatterns = [
    path('', index, name="view_books"),
    path('add/', add, name="add"),
    path('<int:id>/', get, name="get"),
    path('edit/<int:id>', edit, name="edit"),
    path('update/<int:id>', update, name="update"),
    path('delete/<int:id>', delete, name="delete"),
]

