from onlineapp.serilizer import *
from rest_framework.response import Response
from rest_framework.decorators import api_view
from rest_framework import status
from rest_framework.views import APIView


@api_view(['GET','POST','PUT','DELETE'])
def college_api(request, *args, **kwargs):
    if request.method == 'GET':
        if kwargs:
            try:
                clg = College.objects.get(**kwargs)
                print(clg)
                return Response(CollegeSerializer(clg).data)
            except:
                return Response(status=status.HTTP_400_BAD_REQUEST)
        clg=College.objects.all()
        i=CollegeSerializer(clg, many=True)
        return Response(i.data)

    elif request.method=='POST':
        if kwargs:
            return Response(status=status.HTTP_400_BAD_REQUEST)
        college= CollegeSerializer(data= request.data)
        if college.is_valid():
            college.save()
            return Response(status=200)
        return Response(status=status.HTTP_400_BAD_REQUEST)

    elif request.method=='PUT':
        if kwargs:
            try:
                college=College.objects.get(**kwargs)
                serializer = CollegeSerializer(college, data=request.data)
                if serializer.is_valid():
                    serializer.save()
                    return Response(status=200)
            except:
                pass
        return Response(status=400)
    elif request.method=='DELETE':
        if kwargs:
            try:
                college =College.objects.get(**kwargs)
                college.delete()
                return Response(status=200)
            except:
                pass
        return Response(status=400)




class StudentsList(APIView):
    """
    List all students, or create a new snippet.
    """
    def get(self, request, *args, **kwargs):
        try:
            if kwargs:
                students = Student.objects.filter(college__id= kwargs.get('cpk'))
                serializer = StudentSerializer(students, many=True)
                return Response(serializer.data)
        except:
            pass

        return Response(status=400)


    def post(self, request, *args, **kwargs):
        serializer = StudentDetailsSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class StudentDetails(APIView):
    """
    Retrieve, update or delete a snippet instance.
    """
    def get(self, request, *args, **kwargs):
        try:
            if 'spk' in kwargs:
                student = Student.objects.filter(id = kwargs.get('spk'))
                if student[0].college.id == kwargs.get('cpk'):
                    serializer = StudentDetailsSerializer(student[0])
                    return Response(serializer.data)
        except:
            pass

        return Response(status=400)


    def put(self, request, pk, format=None):
        snippet = self.get_object(pk)
        serializer = SnippetSerializer(snippet, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, *args, **kwargs):
        try:
            if 'spk' in kwargs:
                student= Student.objects.get(pk=kwargs.get('spk'))
                if student.college.id== kwargs.get('cpk'):
                    student.delete()
                    return Response(status=200)
        except:
            pass
        return Response(status=400)