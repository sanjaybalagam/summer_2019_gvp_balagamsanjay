from rest_framework.serializers import ModelSerializer
from onlineapp.models import College,Student,MockTest1


class CollegeSerializer(ModelSerializer):
    class Meta:
        model = College
        fields = ('id','name', 'location', 'acronym','contact')


class StudentSerializer(ModelSerializer):
    class Meta:
        model= Student
        fields = ('id','name','dob','email', 'db_folder', 'dropped_out', 'college')


class Mocktest1Serializer(ModelSerializer):
    class Meta:
        model= MockTest1
        fields= ('problem1', 'problem2','problem3', 'problem4','total')


class StudentDetailsSerializer(ModelSerializer):
    mocktest1 = Mocktest1Serializer()
    class Meta:
        model= Student
        fields= ('id','name','dob','email', 'db_folder', 'dropped_out', 'college','mocktest1')

    def create(self, validated_data):
        mocktest_data = validated_data.pop('mocktest1')
        student = Student.objects.create(**validated_data)
        MockTest1.objects.create(student=student, **mocktest_data)
        return student
