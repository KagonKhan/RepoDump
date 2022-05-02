from django.urls import path, include
from .views import index, add, get, edit, update

urlpatterns = [
    path('', index, name="view_news"),
    path('add/', add, name="add"),
    path('<int:id>/', get, name="get"),
    path('edit/<int:id>', edit, name="edit"),
    path('update/<int:id>', update, name="update"),
]

