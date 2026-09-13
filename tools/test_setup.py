"""Host selection, verified extraction and failure-before-mutation checks."""
import io
import tempfile
from pathlib import Path
import tarfile
import unittest
from unittest.mock import patch
import setup_ido
import rom


class SetupTests(unittest.TestCase):
    def test_host_selection(self):
        for osname, arch, expected in [('Linux','x86_64','linux'), ('Linux','aarch64','linux-arm'), ('Darwin','arm64','macos'), ('Darwin','x86_64','macos'), ('Windows','AMD64','windows')]:
            self.assertEqual(setup_ido.host_id(osname, arch), expected)
        for osname, arch in [('Linux','armv7l'), ('Linux','riscv64'), ('Darwin','i386'), ('Windows','ARM64')]:
            with self.assertRaises(ValueError): setup_ido.host_id(osname,arch)

    def test_reject_unsafe_archive_before_extracting(self):
        for name, kind in [('../escape', tarfile.REGTYPE), ('cc', tarfile.SYMTYPE)]:
            with tempfile.TemporaryDirectory() as temp:
                root=Path(temp); archive=root/'bad.tar.gz'; target=root/'out';target.mkdir()
                with tarfile.open(archive,'w:gz') as tar:
                    member=tarfile.TarInfo(name);member.type=kind
                    tar.addfile(member,io.BytesIO())
                with self.assertRaises(ValueError): setup_ido.unpack(archive,target)
                self.assertEqual(list(target.iterdir()), [])

    def test_checksum_failure_preserves_existing_install(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp);target=root/'tools/ido5.3/v1.2/linux';target.mkdir(parents=True)
            (target/'cc').write_bytes(b'old compiler');archive=root/'bad.tar.gz';archive.write_bytes(b'bad')
            with patch.object(setup_ido,'ROOT',root):
                with self.assertRaises(ValueError):setup_ido.install('linux',archive)
            self.assertEqual((target/'cc').read_bytes(),b'old compiler')

    def test_bad_rom_preserves_assets(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp);(root/'assets').mkdir();p=root/'assets/ipl3.bin';p.write_bytes(b'existing')
            (root/'tetrisphere.z64').write_bytes(b'wrong ROM')
            with self.assertRaises(ValueError):rom.extract(root)
            self.assertEqual(p.read_bytes(),b'existing')

    def test_reference_required(self):
        with tempfile.TemporaryDirectory() as temp:
            with self.assertRaisesRegex(ValueError,'Place your original USA ROM'):rom.reference(Path(temp))


if __name__ == '__main__':unittest.main()
