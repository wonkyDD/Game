#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdlib>

/** @todo cmake 빌드 */
// This is a configuration file generated by CMake.
// #include "root_directory.h"

/** @todo getPath 제외하고는 다 static일 필요는 없지 않나? */
class FileSystem
{
private:
    /** @note 함수포인터를 private에 박았음*/
    typedef std::string(*Builder) (const std::string& path);

public:
    static std::string getPath(const std::string& path)
    {
        // static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
        // return (*pathBuilder)(path);
        static Builder b = getPathBuilder();
        return (*b)(path);
    }

private:
    static Builder getPathBuilder()
    {
        if (getRoot() != "")
            return &FileSystem::getPathRelativeRoot;
        else
            return &FileSystem::getPathRelativeBinary;
    }

    static std::string getPathRelativeRoot(const std::string& path)
    {
        return getRoot() + std::string("/") + path;
    }

    static std::string getPathRelativeBinary(const std::string& path)
    {
        return "../../../" + path;
    }

    static std::string const& getRoot()
    {
        /** @todo cmake 빌드 */
         //static char const * envRoot = getenv("LOGL_ROOT_PATH");
         //static char const * givenRoot = (envRoot != nullptr ? envRoot : logl_root);
         //static std::string root = (givenRoot != nullptr ? givenRoot : "");

        /**
         * @todo
         * root 파일경로 (alkagi -> OpenGL)
         *
         * -> 어떻게 cmake빌드했을때
         * `logl_root`를 가진 root_directory.h 파일이 생성되는지 확인할 것.
         *
        */
        static std::string root = "/Users/joseonghyeon/dev/OpenGL";
        return root;
    }

};
#endif