// Jenkinsfile for NvmJIT
pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh "cd nvmjit/jni && make"
      }
    }

    stage('Archive') {
      steps {
        sh "cd nvmjit/jni && make dist"
        archiveArtifacts artifacts: findFiles(glob: 'nvmjit/jni/*.tar.gz')[0].path, fingerprint: true
      }
    }
    
    stage('Cleanup') {
      steps {
        sh "cd nvmjit/jni && make clean"
      }
    }
  }

  environment {
    JAVA_HOME = "${env.JDK_9}"
    BLAKE2B_DIR = "${env.NUCO_LIB}"
  }
}
